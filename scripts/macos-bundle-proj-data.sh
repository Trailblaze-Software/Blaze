#!/usr/bin/env bash
# Copy PROJ's data files (proj.db etc.) into each macOS .app bundle and next to
# blaze-cli in the install tree, so CRS lookups work on a clean Mac.
#
# Why this is needed (issue #36):
#   The bundles ship Homebrew's libproj, whose compiled-in data directory is
#   $(brew --prefix)/share/proj. That exists on CI runners and dev machines but
#   not on a user's Mac, so without bundled data every EPSG lookup fails: LAS
#   files whose CRS is stored as GeoTIFF GeoKeys report "no embedded CRS" and
#   every override_crs value is rejected.
#
#   At startup configure_bundled_proj_data() (src/lib/io/proj_data.cpp) points
#   PROJ at <App>.app/Contents/Resources/proj, or <prefix>/share/proj for
#   blaze-cli. Contents/Resources lives inside the bundle, so it survives
#   Gatekeeper App Translocation.
#
#   Run this BEFORE macdeployqt / macos-fix-deps.sh: those re-sign the bundle,
#   and files added afterwards would invalidate its code seal.
#
# Usage: scripts/macos-bundle-proj-data.sh <staging-prefix> <App.app> [App2.app ...]

set -u

STAGING="${1:-}"
shift || true
[ -n "$STAGING" ] && [ -d "$STAGING" ] || { echo "ERROR: staging dir not found: '$STAGING'" >&2; exit 1; }

PROJ_SRC="$(brew --prefix proj 2>/dev/null)/share/proj"
if [ ! -f "$PROJ_SRC/proj.db" ]; then
    echo "ERROR: proj.db not found in '$PROJ_SRC' (is Homebrew proj installed?)" >&2
    exit 1
fi

# Copy everything except PROJ's optional transformation grids (*.tif), which
# can be large and which PROJ can fetch on demand when networking is enabled.
copy_proj_data() {
    local dest="$1"
    rm -rf "$dest"
    mkdir -p "$(dirname "$dest")"
    cp -R "$PROJ_SRC/" "$dest"
    find "$dest" -name '*.tif' -delete
    [ -f "$dest/proj.db" ] || { echo "ERROR: failed to copy proj.db to $dest" >&2; exit 1; }
}

copy_proj_data "$STAGING/share/proj"
echo "    blaze-cli: bundled PROJ data -> share/proj"

for app in "$@"; do
    [ -d "$app" ] || continue
    copy_proj_data "$app/Contents/Resources/proj"
    echo "    $(basename "$app"): bundled PROJ data -> Contents/Resources/proj"
done
