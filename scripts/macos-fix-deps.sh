#!/usr/bin/env bash
# Make a macOS .app bundle self-contained by pulling in the transitive dylib
# dependencies that macdeployqt misses.
#
# Why this is needed:
#   macdeployqt copies an app's direct dependencies into Contents/Frameworks
#   and rewrites their install names, but it does NOT reliably follow the
#   dependency graph through Homebrew libraries. Homebrew dylibs carry an
#   LC_RPATH of "@loader_path/../lib"; once such a dylib is relocated into
#   Contents/Frameworks that rpath points at a nonexistent Contents/lib, so
#   macdeployqt can't resolve the next library down and silently leaves it out.
#   The bundle then crashes on a clean Mac with e.g.
#       Library not loaded: @rpath/libgeos.3.14.1.dylib
#   (GDAL -> libgeos_c -> libgeos is the classic case; jpeg-xl and the AWS SDK
#   have the same shape).
#
# What it does, for each .app passed as an argument:
#   1. Closure: repeatedly scan the bundle's Mach-O files — the executables in
#      Contents/MacOS, the plugins, and everything in Contents/Frameworks — for
#      @rpath/ or Homebrew absolute dependencies that aren't present yet, locate
#      them on the host (via the Homebrew prefix, so no version numbers are
#      hardcoded) and copy them in, until nothing is missing. Seeding from the
#      executables (not just Frameworks) is what bundles libraries the binary
#      links directly, e.g. libomp. Once a library physically sits in
#      Contents/Frameworks, the app executable's own
#      "@executable_path/../Frameworks" rpath resolves the @rpath reference, so
#      the broken per-library rpath does not need rewriting.
#   2. Normalize: rewrite every bundled dylib's id to @rpath/<name> and repoint
#      any remaining Homebrew-absolute dependency references (including OpenCV's
#      hardcoded self-referential ids) to @rpath/<name>.
#   3. Re-sign: ad-hoc codesign everything that was modified. Apple Silicon
#      refuses to load dylibs whose signature install_name_tool invalidated, so
#      this is mandatory for the arm64 build, and harmless on Intel.
#   4. Verify: exit non-zero if any @rpath/*.dylib dependency is still
#      unresolved.
#
# Implementation note: this deliberately does NOT use `set -e`/`pipefail`, and
# it reads each dependency list fully into a variable before iterating (rather
# than piping a live `otool` into a loop that runs install_name_tool). A live
# pipe feeding a loop that runs crash-prone tools, combined with `set -e`, can
# tear the shell down mid-pipe and abort the whole script. Errors are handled
# explicitly and the final verify determines success.
#
# Usage: scripts/macos-fix-deps.sh path/to/Foo.app [path/to/Bar.app ...]

set -u

BREW_PREFIX="$(brew --prefix 2>/dev/null || echo /usr/local)"

# Directories to search for a library referenced only by basename (@rpath/X).
SEARCH_DIRS=("$BREW_PREFIX/lib")
for d in "$BREW_PREFIX"/opt/*/lib; do
    [ -d "$d" ] && SEARCH_DIRS+=("$d")
done

# Print a dylib/executable's dependency install names (skipping the header).
deps_of() { otool -L "$1" 2>/dev/null | tail -n +2 | awk '{print $1}'; }

# Locate a library by basename on the host. Echoes the path, or returns 1.
find_host_lib() {
    local name="$1" d hit
    for d in "${SEARCH_DIRS[@]}"; do
        [ -f "$d/$name" ] && { printf '%s\n' "$d/$name"; return 0; }
    done
    # Fallback: some Homebrew libraries live in nested directories the flat
    # opt/*/lib globs miss — notably gcc, which keeps libgcc_s / libgfortran
    # under opt/gcc/lib/gcc/current. Search the real Cellar tree (no symlinks
    # to chase) for the basename and take the first match.
    hit="$(find "$BREW_PREFIX/Cellar" -name "$name" -type f 2>/dev/null | head -1)"
    [ -n "$hit" ] && { printf '%s\n' "$hit"; return 0; }
    return 1
}

# All Mach-O files to walk as roots of the dependency closure: everything
# already in Frameworks, the app's main executables, and bundled plugins.
# Seeding from the executables (not just Frameworks) is what pulls in libraries
# the binary links DIRECTLY — e.g. libomp from OpenMP — so they get bundled,
# id-normalized and signed by this one code path instead of a bespoke step.
closure_roots() {
    local app="$1"
    ls "$app"/Contents/Frameworks/*.dylib 2>/dev/null
    find "$app/Contents/MacOS" -type f 2>/dev/null
    find "$app/Contents/PlugIns" -name '*.dylib' 2>/dev/null
}

# Phase 1: copy missing dependencies into Frameworks until the graph is closed.
copy_missing() {
    local app="$1" fw="$app/Contents/Frameworks"
    local progressed=1 round=0 lib dep depbase src deps roots
    while [ "$progressed" -eq 1 ] && [ "$round" -lt 25 ]; do
        progressed=0
        round=$((round + 1))
        roots="$(closure_roots "$app")"
        while IFS= read -r lib; do
            [ -e "$lib" ] || continue
            # Skip non-Mach-O entries (e.g. shell scripts that live in MacOS/).
            case "$(file -b "$lib" 2>/dev/null)" in *Mach-O*) ;; *) continue ;; esac
            deps="$(deps_of "$lib")" # consume the pipe fully, THEN iterate
            while IFS= read -r dep; do
                [ -n "$dep" ] || continue
                case "$dep" in
                    @rpath/*.dylib) depbase="${dep#@rpath/}" ;;
                    "$BREW_PREFIX"/*.dylib | /usr/local/*.dylib) depbase="$(basename "$dep")" ;;
                    *) continue ;;
                esac
                [ -f "$fw/$depbase" ] && continue
                src=""
                if [ "${dep:0:1}" = "/" ] && [ -f "$dep" ]; then
                    src="$dep"
                else
                    src="$(find_host_lib "$depbase" 2>/dev/null || true)"
                fi
                if [ -n "$src" ] && [ -f "$src" ]; then
                    if cp "$src" "$fw/$depbase"; then
                        chmod u+w "$fw/$depbase" 2>/dev/null
                        echo "    + bundled $depbase"
                        progressed=1
                    fi
                else
                    echo "    ! could not locate $depbase (needed by $(basename "$lib"))" >&2
                fi
            done <<EOF
$deps
EOF
        done <<ROOTS
$roots
ROOTS
    done
}

# Phase 2: normalize install names so every lookup resolves in-bundle.
normalize_one() {
    # $1 = mach-o file, $2 = Frameworks dir, $3 = "id" to also set the id
    local f="$1" fw="$2" setid="${3:-}" dep db deps
    chmod u+w "$f" 2>/dev/null
    if [ "$setid" = "id" ]; then
        install_name_tool -id "@rpath/$(basename "$f")" "$f" 2>/dev/null
    fi
    deps="$(deps_of "$f")"
    while IFS= read -r dep; do
        [ -n "$dep" ] || continue
        case "$dep" in
            "$BREW_PREFIX"/*.dylib | /usr/local/*.dylib)
                db="$(basename "$dep")"
                if [ -f "$fw/$db" ]; then
                    install_name_tool -change "$dep" "@rpath/$db" "$f" 2>/dev/null
                fi
                ;;
        esac
    done <<EOF
$deps
EOF
}

# Frameworks need their own pass: a framework's load name is the multi-segment
# path Foo.framework/Versions/A/Foo, not a leaf Foo.dylib, so normalize_one's
# basename logic can't id them. Homebrew/Qt leave some framework binaries with
# an absolute self-id (e.g. /usr/local/opt/qtbase/lib/QtDBus.framework/.../QtDBus)
# and absolute references to sibling frameworks; rewrite both to the bundle's
# @rpath/<relative-path> so they resolve on a machine without Qt installed.
normalize_frameworks() {
    local app="$1" fw="$app/Contents/Frameworks" binfile relpath dep drel deps bins
    # Real versioned binaries only (-type f skips the Current/leaf symlinks).
    bins="$(find "$fw" -type f -path '*.framework/Versions/*' 2>/dev/null)"
    while IFS= read -r binfile; do
        [ -n "$binfile" ] || continue
        case "$(file -b "$binfile" 2>/dev/null)" in *Mach-O*) ;; *) continue ;; esac
        chmod u+w "$binfile" 2>/dev/null
        relpath="${binfile#"$fw"/}"
        install_name_tool -id "@rpath/$relpath" "$binfile" 2>/dev/null
        deps="$(deps_of "$binfile")"
        while IFS= read -r dep; do
            case "$dep" in
                "$BREW_PREFIX"/*.framework/*|/usr/local/*.framework/*)
                    # .../lib/QtCore.framework/Versions/A/QtCore -> QtCore.framework/Versions/A/QtCore
                    drel="$(printf '%s\n' "$dep" | sed -E 's#^.*/([^/]+\.framework/)#\1#')"
                    [ -e "$fw/$drel" ] && install_name_tool -change "$dep" "@rpath/$drel" "$binfile" 2>/dev/null
                    ;;
                "$BREW_PREFIX"/*.dylib|/usr/local/*.dylib)
                    drel="$(basename "$dep")"
                    [ -f "$fw/$drel" ] && install_name_tool -change "$dep" "@rpath/$drel" "$binfile" 2>/dev/null
                    ;;
            esac
        done <<EOF
$deps
EOF
    done <<FWBINS
$bins
FWBINS
}

normalize() {
    local app="$1" fw="$app/Contents/Frameworks" lib exe
    for lib in "$fw"/*.dylib; do
        [ -e "$lib" ] || continue
        normalize_one "$lib" "$fw" id
    done
    normalize_frameworks "$app"
    for exe in "$app/Contents/MacOS/"*; do
        [ -f "$exe" ] || continue
        case "$(file -b "$exe" 2>/dev/null)" in *Mach-O*) ;; *) continue ;; esac
        normalize_one "$exe" "$fw"
    done
}

# Phase 3: ad-hoc re-sign everything, inside-out.
#
# Order matters: codesign seals a container over its current contents, so every
# nested item must be signed BEFORE the thing that contains it, and the .app
# itself signed last. The critical, easy-to-miss case is frameworks: a
# framework's binary is Contents/Frameworks/QtGui.framework/Versions/A/QtGui —
# it has NO .dylib extension, so the *.dylib sweep skips it. The official Qt
# frameworks ship with a Developer-ID + hardened-runtime signature; the
# install_name_tool edits above invalidate it, and if we never re-sign the
# framework the whole app seal is invalid and Gatekeeper reports the downloaded
# app as "damaged and can't be opened". So we explicitly sign each framework.
resign() {
    local app="$1" f exe fw
    # 1. Every dylib anywhere (loose libs, plugins, any nested inside frameworks)
    #    so the containers below seal over already-valid contents.
    while IFS= read -r f; do
        [ -n "$f" ] && codesign --force --sign - "$f" 2>/dev/null
    done <<EOF
$(find "$app" -name '*.dylib')
EOF
    # 2. Each nested framework (signs its versioned binary + seals its resources).
    for fw in "$app"/Contents/Frameworks/*.framework; do
        [ -d "$fw" ] && codesign --force --sign - "$fw" 2>/dev/null
    done
    # 3. Main executables.
    for exe in "$app/Contents/MacOS/"*; do
        [ -f "$exe" ] || continue
        case "$(file -b "$exe" 2>/dev/null)" in *Mach-O*) codesign --force --sign - "$exe" 2>/dev/null ;; esac
    done
    # 4. The app bundle last.
    codesign --force --sign - "$app" 2>/dev/null
}

# Phase 0: drop plugins Blaze does not use whose own (heavy) framework
# dependencies macdeployqt fails to bundle. The virtual-keyboard input method
# (platforminputcontexts) drags in the QtQuick/QtVirtualKeyboard QML stack, and
# the PDF image format (imageformats/libqpdf) needs QtPdf — neither is used by a
# desktop GIS app, and bundling those frameworks just to satisfy an unused
# plugin would bloat the DMG. Removing the plugin removes the dependency, so the
# closure stays self-contained.
prune_unused_plugins() {
    local app="$1" p
    for p in \
        Contents/PlugIns/platforminputcontexts \
        Contents/PlugIns/imageformats/libqpdf.dylib
    do
        if [ -e "$app/$p" ]; then
            rm -rf "$app/$p"
            echo "    - pruned ${p#Contents/PlugIns/}"
        fi
    done
}

# Phase 4: report any @rpath/*.dylib dependency still unresolved.
verify() {
    local app="$1" fw="$app/Contents/Frameworks" missing=0 lib dep db deps
    for lib in "$fw"/*.dylib "$app/Contents/MacOS/"*; do
        [ -f "$lib" ] || continue
        deps="$(deps_of "$lib")"
        while IFS= read -r dep; do
            case "$dep" in
                @rpath/*.dylib)
                    db="${dep#@rpath/}"
                    if [ ! -f "$fw/$db" ]; then
                        echo "    MISSING: $db (needed by $(basename "$lib"))" >&2
                        missing=1
                    fi
                    ;;
            esac
        done <<EOF
$deps
EOF
    done
    return $missing
}

rc=0
[ "$#" -ge 1 ] || { echo "usage: $0 App.app [App2.app ...]" >&2; exit 2; }
for app in "$@"; do
    if [ ! -d "$app/Contents/Frameworks" ]; then
        echo "==> $app: no Contents/Frameworks, skipping"
        continue
    fi
    echo "==> Fixing $app"
    prune_unused_plugins "$app"
    copy_missing "$app"
    normalize "$app"
    resign "$app"
    if verify "$app"; then
        echo "    OK: all @rpath dependencies resolve inside the bundle"
    else
        echo "    FAILED: unresolved dependencies remain in $app" >&2
        rc=1
    fi
done
exit $rc
