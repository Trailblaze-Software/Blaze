#!/usr/bin/env bash
# Copy PROJ's data (proj.db etc.) into each .app as Contents/Resources/proj.
#
# The bundles ship Homebrew's libproj, whose compiled-in data dir doesn't exist
# on a clean Mac; without proj.db every EPSG lookup fails (issue #36). At
# startup configure_bundled_proj_data() points PROJ at the bundled copy.
# Run BEFORE macdeployqt/macos-fix-deps.sh so the files are covered by signing.
#
# Usage: scripts/macos-bundle-proj-data.sh <App.app> [App2.app ...]

set -eu

PROJ_SRC="$(brew --prefix proj)/share/proj"
[ -f "$PROJ_SRC/proj.db" ] || { echo "ERROR: no proj.db in $PROJ_SRC" >&2; exit 1; }

for app in "$@"; do
    dest="$app/Contents/Resources/proj"
    rm -rf "$dest"
    mkdir -p "$app/Contents/Resources"
    cp -R "$PROJ_SRC/" "$dest"
    # Optional transformation grids can be large; PROJ can fetch them on demand.
    find "$dest" -name '*.tif' -delete
    echo "    $(basename "$app"): bundled PROJ data -> Contents/Resources/proj"
done
