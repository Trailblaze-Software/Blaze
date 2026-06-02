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
# 6. Bundle transitive deps, normalize install names, and re-sign
#
# Delegate to the shared scripts/macos-fix-deps.sh (also used by the CI release
# workflow) so there is a single source of truth: it pulls in any transitive
# libraries macdeployqt missed, rewrites hardcoded Homebrew install names to
# @rpath, and — crucially — ad-hoc re-signs every modified binary. Without the
# re-sign the app seal is invalid and a downloaded copy is rejected by
# Gatekeeper as "damaged".
# ---------------------------------------------------------------------------
echo "==> Bundling transitive deps + normalizing + re-signing..."
for APP in "$STAGING"/Blaze.app "$STAGING"/Blaze3D.app; do
    [ -d "$APP/Contents/Frameworks" ] || continue
    scripts/macos-fix-deps.sh "$APP"
done

# ---------------------------------------------------------------------------
# 6b. Verify each bundle is self-contained and validly signed
#
# Hard gate before we ship: macos-verify-bundle.sh fails if any bundle still
# references a host-only library (Homebrew/Qt/Cellar) or has an invalid code
# seal — i.e. anything that would crash or show "damaged" on a clean Mac. This
# is the same check the CI release workflow runs.
# ---------------------------------------------------------------------------
echo "==> Verifying bundles are self-contained + validly signed..."
VERIFY_APPS=()
for APP in "$STAGING"/Blaze.app "$STAGING"/Blaze3D.app; do
    [ -d "$APP/Contents/Frameworks" ] && VERIFY_APPS+=("$APP")
done
scripts/macos-verify-bundle.sh "${VERIFY_APPS[@]}"

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
