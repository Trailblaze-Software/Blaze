#!/usr/bin/env bash
# Verify a macOS .app bundle is self-contained AND validly signed, so it will
# run on a clean Mac — one with no Homebrew, no Qt, no developer tooling.
#
# Why this exists:
#   CI runners and dev machines already have Qt/GDAL/Homebrew installed, so a
#   half-bundled app can silently fall back to those system copies and appear to
#   work, then crash for a user who has none of them. And an app whose code seal
#   was invalidated by install_name_tool (e.g. a framework modified after it was
#   signed) is reported by Gatekeeper as "damaged and can't be opened". Neither
#   failure is caught by running blaze-cli. This script is the gate that makes
#   "green in CI" actually mean "runs on a clean Mac". Run it AFTER
#   macos-fix-deps.sh, before building the DMG.
#
# It hard-fails (exit 1) if either check fails, for any .app passed:
#
#   1. Dependency closure — every dependency of every Mach-O in the bundle must
#      resolve to one of:
#        * something inside the bundle (an @rpath/@loader_path/@executable_path
#          reference whose basename is present in the bundle), or
#        * /usr/lib/** or /System/Library/** (the only library dirs guaranteed
#          to exist on stock macOS).
#      Any absolute reference into /opt/homebrew, /usr/local, a Qt install dir,
#      the Cellar, a user home, etc. — or an @rpath lib that isn't bundled —
#      is a guaranteed crash on a clean machine and fails the check.
#
#   2. Signature — `codesign --verify --deep --strict` must pass.
#
# Usage: scripts/macos-verify-bundle.sh path/to/Foo.app [path/to/Bar.app ...]

set -u

# Every Mach-O binary in the bundle: loose dylibs, plugins, framework binaries
# (which have no .dylib extension), and the executables in Contents/MacOS.
list_macho() {
    local app="$1" fw name exe
    find "$app" -name '*.dylib' 2>/dev/null
    for fw in "$app"/Contents/Frameworks/*.framework; do
        [ -d "$fw" ] || continue
        name="$(basename "$fw" .framework)"
        [ -e "$fw/$name" ] && printf '%s\n' "$fw/$name"
    done
    for exe in "$app/Contents/MacOS/"*; do
        [ -f "$exe" ] && printf '%s\n' "$exe"
    done
}

check_closure() {
    local app="$1" bad=0 file dep base macho index
    macho="$(list_macho "$app")"
    # Precompute the set of file basenames present anywhere in the bundle, so a
    # bundle-relative dependency (@rpath/@loader_path/@executable_path) can be
    # resolved by a fast membership test instead of a find-per-dependency.
    index="$(find "$app" 2>/dev/null | sed 's#.*/##' | sort -u)"
    while IFS= read -r file; do
        [ -n "$file" ] || continue
        # tail -n +2 drops the otool header line; for a dylib the next line is
        # its own id, which we tolerate (self-reference is harmless).
        while IFS= read -r dep; do
            dep="${dep%% (*}"            # strip " (compatibility version ...)"
            dep="${dep#"${dep%%[![:space:]]*}"}"  # ltrim
            [ -n "$dep" ] || continue
            case "$dep" in
                /usr/lib/*|/System/Library/*) ;;                  # stock macOS — OK
                @executable_path/*|@loader_path/*|@rpath/*)
                    base="${dep##*/}"
                    if ! printf '%s\n' "$index" | grep -qxF "$base"; then
                        echo "    UNRESOLVED: $dep (needed by ${file#"$app"/})" >&2
                        bad=1
                    fi
                    ;;
                /*)
                    # Any other absolute path = host-specific, won't exist on a
                    # clean Mac (Homebrew, Qt install dir, Cellar, /Users/...).
                    echo "    NON-PORTABLE: $dep (needed by ${file#"$app"/})" >&2
                    bad=1
                    ;;
            esac
        done <<INNER
$(otool -L "$file" 2>/dev/null | tail -n +2 | awk '{print $1}')
INNER
    done <<OUTER
$macho
OUTER
    return $bad
}

rc=0
[ "$#" -ge 1 ] || { echo "usage: $0 App.app [App2.app ...]" >&2; exit 2; }
for app in "$@"; do
    if [ ! -d "$app" ]; then
        echo "==> $app: not found, skipping" >&2
        rc=1; continue
    fi
    echo "==> Verifying $app"

    if check_closure "$app"; then
        echo "    closure OK: all dependencies are in-bundle or stock macOS"
    else
        echo "    closure FAILED: bundle is not self-contained (see above)" >&2
        rc=1
    fi

    if codesign --verify --deep --strict --verbose=2 "$app" >/tmp/codesign-verify.$$ 2>&1; then
        echo "    signature OK: valid on disk, satisfies Designated Requirement"
    else
        echo "    signature FAILED: Gatekeeper would reject this as damaged" >&2
        tail -3 /tmp/codesign-verify.$$ >&2
        rc=1
    fi
    rm -f /tmp/codesign-verify.$$
done
exit $rc
