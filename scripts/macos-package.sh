#!/bin/bash
# Build and package Blaze as a macOS DMG using the local Homebrew toolchain.
#
# Usage:
#   ./scripts/macos-package.sh               # builds, packages, produces DMG
#   ./scripts/macos-package.sh --skip-build  # skip cmake build (reuse macos-build/)
#
# Output: macos-build/Blaze-<version>-macOS-<arch>.dmg
#
# Prerequisites (install with ./scripts/install-macos-deps.sh):
#   brew install cmake ninja ccache gdal opencv qt@6 libomp openblas lapack
#
# Note: this uses Homebrew's macdeployqt, which requires manual post-processing
# to add the Qt platform plugins it misses (see step 5 below). The official CI
# release uses the Qt installer's macdeployqt instead, which handles everything
# automatically.

set -e
cd "$(dirname "$0")/.."

# ---------------------------------------------------------------------------
# 0. Parse arguments
# ---------------------------------------------------------------------------
SKIP_BUILD=false
for arg in "$@"; do
    case "$arg" in
        --skip-build) SKIP_BUILD=true ;;
        *) echo "Unknown argument: $arg"; exit 1 ;;
    esac
done

# ---------------------------------------------------------------------------
# 1. Build (unless --skip-build)
# ---------------------------------------------------------------------------
if [ "$SKIP_BUILD" = false ]; then
    echo "==> Building..."
    ./scripts/macos-build.sh
fi

BUILD_DIR="macos-build"
if [ ! -d "$BUILD_DIR/Blaze.app" ]; then
    echo "Error: $BUILD_DIR/Blaze.app not found. Run without --skip-build first."
    exit 1
fi

# ---------------------------------------------------------------------------
# 2. Resolve tool paths
# ---------------------------------------------------------------------------
QT_PREFIX=$(brew --prefix qtbase 2>/dev/null || brew --prefix qt@6 2>/dev/null || true)
if [ -z "$QT_PREFIX" ]; then
    echo "Error: Qt6 not found via Homebrew. Run ./scripts/install-macos-deps.sh"
    exit 1
fi

MACDEPLOYQT="$QT_PREFIX/bin/macdeployqt"
if [ ! -x "$MACDEPLOYQT" ]; then
    echo "Error: macdeployqt not found at $MACDEPLOYQT"
    exit 1
fi

QT_PLUGINS="$QT_PREFIX/share/qt/plugins"
if [ ! -d "$QT_PLUGINS" ]; then
    QT_PLUGINS="$QT_PREFIX/plugins"
fi

# ---------------------------------------------------------------------------
# 3. Stage install
# ---------------------------------------------------------------------------
STAGING="$BUILD_DIR/_staging"
rm -rf "$STAGING"
echo "==> Staging install..."
cmake --install "$BUILD_DIR" --prefix "$STAGING" --config Release 2>&1 \
    | grep -v "^-- Install\|^-- Up-to-date"

# ---------------------------------------------------------------------------
# 4. Bundle Qt frameworks with macdeployqt
#
# Homebrew's macdeployqt can abort mid-process and DELETE the .app it was
# working on (it encounters many install_name_tool errors due to Homebrew's
# non-standard @executable_path rpaths and split-package layout). To protect
# against this, we run macdeployqt on a temporary copy of each app and only
# replace the staging app if bundling produced a valid Frameworks directory.
# Verbose output goes to a log file to keep the terminal readable.
# ---------------------------------------------------------------------------
echo "==> Bundling Qt frameworks with macdeployqt..."

run_macdeployqt() {
    local APP="$1"
    local name
    name=$(basename "$APP")
    local log="$BUILD_DIR/macdeployqt-$name.log"
    local tmp="${APP}.deploytmp"

    rm -rf "$tmp"
    cp -r "$APP" "$tmp"

    printf "    %-20s" "$name"
    "$MACDEPLOYQT" "$tmp" -always-overwrite > "$log" 2>&1 || true

    local fw_count=0
    [ -d "$tmp/Contents/Frameworks" ] && \
        fw_count=$(ls "$tmp/Contents/Frameworks/" 2>/dev/null | wc -l | tr -d ' ')

    if [ "$fw_count" -gt 5 ]; then
        rm -rf "$APP"
        mv "$tmp" "$APP"
        echo "OK ($fw_count items bundled)"
    else
        rm -rf "$tmp"
        echo "WARN: macdeployqt failed to bundle (check $log) — app will not run on other Macs"
    fi
}

for APP in "$STAGING"/Blaze.app "$STAGING"/Blaze3D.app; do
    [ -d "$APP" ] || continue
    run_macdeployqt "$APP"
done

# ---------------------------------------------------------------------------
# 5. Fix Qt plugins that Homebrew's macdeployqt misses
#
# macdeployqt only scans the keg it was installed from (qtbase) and misses
# plugins that ship in other Homebrew kegs. Without platforms/libqcocoa.dylib
# the app crashes immediately on launch ("Could not find the Qt platform
# plugin cocoa").
# ---------------------------------------------------------------------------
echo "==> Adding missing Qt platform plugins..."
QTSVG_PLUGINS="$(brew --prefix qtsvg 2>/dev/null)/share/qt/plugins"

for APP in "$STAGING"/Blaze.app "$STAGING"/Blaze3D.app; do
    [ -d "$APP/Contents/Frameworks" ] || continue
    PLUGINS="$APP/Contents/PlugIns"

    mkdir -p "$PLUGINS/platforms"
    cp "$QT_PLUGINS/platforms/libqcocoa.dylib" "$PLUGINS/platforms/"
    chmod 755 "$PLUGINS/platforms/libqcocoa.dylib"

    mkdir -p "$PLUGINS/styles"
    cp "$QT_PLUGINS/styles/libqmacstyle.dylib" "$PLUGINS/styles/"
    chmod 755 "$PLUGINS/styles/libqmacstyle.dylib"

    if [ -d "$QTSVG_PLUGINS/iconengines" ] && \
       [ -d "$APP/Contents/Frameworks/QtSvg.framework" ]; then
        mkdir -p "$PLUGINS/iconengines"
        cp "$QTSVG_PLUGINS/iconengines/libqsvgicon.dylib" "$PLUGINS/iconengines/"
        chmod 755 "$PLUGINS/iconengines/libqsvgicon.dylib"
    fi

    echo "    $(basename $APP): platforms styles $(ls $PLUGINS | grep -v 'platforms\|styles\|images\|platform' | tr '\n' ' ')"
done

# ---------------------------------------------------------------------------
# 6. Fix hardcoded Homebrew library paths
#
# Some Homebrew dylibs embed their Cellar/opt install path as their own
# LC_ID_DYLIB. macdeployqt copies them but doesn't update the ID, so dyld
# can't match them when other libraries look them up by name. We rewrite each
# ID to @rpath/<name> and fix every caller in the same bundle.
# ---------------------------------------------------------------------------
echo "==> Fixing hardcoded Homebrew library IDs..."

fix_abs_id() {
    local APP="$1"
    local FW="$APP/Contents/Frameworks"
    local MACOS="$APP/Contents/MacOS"

    [ -d "$FW" ] || return

    # First pass: collect old→new pairs and fix each dylib's self-ID.
    # Write to a temp file so the second pass can iterate without bash 4
    # associative arrays (macOS ships bash 3.2).
    local pairs
    pairs=$(mktemp)
    for lib in "$FW"/*.dylib; do
        [ -f "$lib" ] || continue
        local old_id
        old_id=$(otool -D "$lib" 2>/dev/null | tail -1)
        case "$old_id" in
            /usr/local/*)
                local libname new_id
                libname=$(basename "$lib")
                new_id="@rpath/$libname"
                echo "$old_id|$new_id" >> "$pairs"
                chmod 755 "$lib"
                install_name_tool -id "$new_id" "$lib" 2>/dev/null || true
                ;;
        esac
    done

    local count
    count=$(wc -l < "$pairs" | tr -d ' ')
    if [ "$count" -eq 0 ]; then
        rm "$pairs"
        return
    fi

    # Second pass: fix every caller (main binary + all dylibs).
    for f in "$MACOS"/* "$FW"/*.dylib; do
        [ -f "$f" ] || continue
        while IFS='|' read -r old new; do
            if otool -L "$f" 2>/dev/null | grep -qF "$old"; then
                chmod 755 "$f"
                install_name_tool -change "$old" "$new" "$f" 2>/dev/null || true
            fi
        done < "$pairs"
    done
    rm "$pairs"

    echo "    $(basename $APP): fixed $count hardcoded IDs"
}

for APP in "$STAGING"/Blaze.app "$STAGING"/Blaze3D.app; do
    [ -d "$APP" ] || continue
    fix_abs_id "$APP"
done

# ---------------------------------------------------------------------------
# 7. Package as DMG
# ---------------------------------------------------------------------------
VERSION=$(cmake -L -N "$BUILD_DIR" 2>/dev/null \
    | grep "CMAKE_PROJECT_VERSION" | head -1 | cut -d= -f2 || true)
[ -z "$VERSION" ] && VERSION="dev"
ARCH=$(uname -m)
DMG="$BUILD_DIR/Blaze-${VERSION}-macOS-${ARCH}.dmg"

echo "==> Creating $DMG..."
hdiutil create \
    -volname "Blaze" \
    -srcfolder "$STAGING" \
    -ov -format UDZO \
    "$DMG" 2>&1 | grep -v "^Checksumming\|^  \|^verified\|^created:"

rm -rf "$STAGING"
echo ""
echo "Done: $DMG ($(du -sh "$DMG" | cut -f1))"
