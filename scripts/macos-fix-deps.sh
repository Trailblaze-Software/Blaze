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
#   1. Closure: repeatedly scan Contents/Frameworks for @rpath/ or Homebrew
#      absolute dependencies that aren't present yet, locate them on the host
#      (via the Homebrew prefix, so no version numbers are hardcoded) and copy
#      them in, until nothing is missing.
#   2. Normalize: rewrite every bundled dylib's id to @rpath/<name>, repoint the
#      broken "@loader_path/../lib" rpath at "@loader_path", and rewrite any
#      remaining Homebrew-absolute dependency references (incl. OpenCV's
#      hardcoded self-referential ids) to @rpath/<name>.
#   3. Re-sign: ad-hoc codesign everything that was modified. Apple Silicon
#      refuses to load dylibs whose signature install_name_tool invalidated, so
#      this is mandatory for the arm64 build, and harmless on Intel.
#   4. Verify: fail if any @rpath/*.dylib dependency is still unresolved.
#
# Usage: scripts/macos-fix-deps.sh path/to/Foo.app [path/to/Bar.app ...]

set -euo pipefail

BREW_PREFIX="$(brew --prefix 2>/dev/null || echo /usr/local)"

# Directories to search for a library referenced only by basename (@rpath/X).
SEARCH_DIRS=("$BREW_PREFIX/lib")
for d in "$BREW_PREFIX"/opt/*/lib; do
    [ -d "$d" ] && SEARCH_DIRS+=("$d")
done

# Print a dylib/executable's dependency install names (skip the header line;
# the id line of a dylib is harmless here and filtered downstream).
deps_of() { otool -L "$1" 2>/dev/null | tail -n +2 | awk '{print $1}'; }

# Locate a library by basename on the host. Echoes the path, or returns 1.
find_host_lib() {
    local name="$1" d
    for d in "${SEARCH_DIRS[@]}"; do
        [ -f "$d/$name" ] && { printf '%s\n' "$d/$name"; return 0; }
    done
    return 1
}

# Phase 1: copy missing dependencies into Frameworks until the graph is closed.
copy_missing() {
    local fw="$1"
    local progressed=1 round=0 lib dep depbase src
    while [ "$progressed" -eq 1 ]; do
        progressed=0
        round=$((round + 1))
        for lib in "$fw"/*.dylib; do
            [ -e "$lib" ] || continue
            while IFS= read -r dep; do
                case "$dep" in
                    @rpath/*.dylib) depbase="${dep#@rpath/}" ;;
                    "$BREW_PREFIX"/*.dylib | /usr/local/*.dylib) depbase="$(basename "$dep")" ;;
                    *) continue ;;
                esac
                [ -f "$fw/$depbase" ] && continue
                if [ "${dep:0:1}" = "/" ] && [ -f "$dep" ]; then
                    src="$dep"
                else
                    src="$(find_host_lib "$depbase" || true)"
                fi
                if [ -n "${src:-}" ] && [ -f "$src" ]; then
                    cp "$src" "$fw/$depbase"
                    chmod u+w "$fw/$depbase"
                    echo "    + bundled $depbase"
                    progressed=1
                else
                    echo "    ! could not locate $depbase (needed by $(basename "$lib"))" >&2
                fi
            done < <(deps_of "$lib")
        done
        [ "$round" -gt 25 ] && break
    done
    return 0
}

# Phase 2: normalize install names / rpaths so every lookup resolves in-bundle.
normalize() {
    local app="$1"
    local fw="$app/Contents/Frameworks"
    local lib base dep db rp exe

    for lib in "$fw"/*.dylib; do
        [ -e "$lib" ] || continue
        base="$(basename "$lib")"
        chmod u+w "$lib"
        install_name_tool -id "@rpath/$base" "$lib" 2>/dev/null || true
        # Repoint the broken "@loader_path/../lib" rpath at the Frameworks dir
        # the library now lives in.
        while IFS= read -r rp; do
            [ "$rp" = "@loader_path/../lib" ] &&
                install_name_tool -rpath "@loader_path/../lib" "@loader_path" "$lib" 2>/dev/null || true
        done < <(otool -l "$lib" | awk '/LC_RPATH/{f=1} f&&/ path /{print $2; f=0}')
        # Repoint any Homebrew-absolute dependency that is now bundled.
        while IFS= read -r dep; do
            case "$dep" in
                "$BREW_PREFIX"/*.dylib | /usr/local/*.dylib)
                    db="$(basename "$dep")"
                    [ -f "$fw/$db" ] &&
                        install_name_tool -change "$dep" "@rpath/$db" "$lib" 2>/dev/null || true
                    ;;
            esac
        done < <(deps_of "$lib")
    done

    # Fix the same Homebrew-absolute references in the Mach-O executables.
    for exe in "$app/Contents/MacOS/"*; do
        [ -f "$exe" ] || continue
        case "$(file -b "$exe" 2>/dev/null)" in *Mach-O*) ;; *) continue ;; esac
        while IFS= read -r dep; do
            case "$dep" in
                "$BREW_PREFIX"/*.dylib | /usr/local/*.dylib)
                    db="$(basename "$dep")"
                    [ -f "$fw/$db" ] &&
                        install_name_tool -change "$dep" "@rpath/$db" "$exe" 2>/dev/null || true
                    ;;
            esac
        done < <(deps_of "$exe")
    done
    return 0
}

# Phase 3: ad-hoc re-sign everything install_name_tool touched.
resign() {
    local app="$1"
    find "$app" -name '*.dylib' -exec codesign --remove-signature {} + 2>/dev/null || true
    find "$app" -name '*.dylib' -exec codesign --force --sign - {} + 2>/dev/null || true
    local exe
    for exe in "$app/Contents/MacOS/"*; do
        [ -f "$exe" ] || continue
        case "$(file -b "$exe" 2>/dev/null)" in *Mach-O*) ;; *) continue ;; esac
        codesign --force --sign - "$exe" 2>/dev/null || true
    done
    codesign --force --sign - "$app" 2>/dev/null || true
    return 0
}

# Phase 4: fail if any @rpath/*.dylib dependency is still unresolved.
verify() {
    local app="$1"
    local fw="$app/Contents/Frameworks"
    local missing=0 lib dep db
    for lib in "$fw"/*.dylib "$app/Contents/MacOS/"*; do
        [ -f "$lib" ] || continue
        while IFS= read -r dep; do
            case "$dep" in
                @rpath/*.dylib)
                    db="${dep#@rpath/}"
                    [ -f "$fw/$db" ] || {
                        echo "    MISSING: $db (needed by $(basename "$lib"))" >&2
                        missing=1
                    }
                    ;;
            esac
        done < <(deps_of "$lib")
    done
    return $missing
}

main() {
    [ "$#" -ge 1 ] || { echo "usage: $0 App.app [App2.app ...]" >&2; exit 2; }
    for app in "$@"; do
        if [ ! -d "$app/Contents/Frameworks" ]; then
            echo "==> $app: no Contents/Frameworks, skipping"
            continue
        fi
        echo "==> Fixing $app"
        copy_missing "$app/Contents/Frameworks"
        normalize "$app"
        resign "$app"
        if verify "$app"; then
            echo "    OK: all @rpath dependencies resolve inside the bundle"
        else
            echo "    FAILED: unresolved dependencies remain in $app" >&2
            exit 1
        fi
    done
}

main "$@"
