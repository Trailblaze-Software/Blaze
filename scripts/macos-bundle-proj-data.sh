#!/usr/bin/env bash
# Copy PROJ's data (proj.db etc.) to each given directory: <App>.app/Contents/
# Resources/proj for the GUI apps, <prefix>/share/proj for blaze-cli.
#
# The DMG ships Homebrew's libproj, whose compiled-in data dir doesn't exist on
# a clean Mac; without proj.db every EPSG lookup fails (issue #36). At startup
# configure_bundled_proj_data() points PROJ at the bundled copy.
# Run BEFORE macdeployqt/macos-fix-deps.sh so the files are covered by signing.
#
# Usage: scripts/macos-bundle-proj-data.sh <dest-dir> [dest-dir ...]

set -eu

PROJ_SRC="$(brew --prefix proj)/share/proj"
[ -f "$PROJ_SRC/proj.db" ] || { echo "ERROR: no proj.db in $PROJ_SRC" >&2; exit 1; }

for dest in "$@"; do
    rm -rf "$dest"
    mkdir -p "$(dirname "$dest")"
    cp -R "$PROJ_SRC/" "$dest"
    # Optional transformation grids can be large; PROJ can fetch them on demand.
    find "$dest" -name '*.tif' -delete
    echo "    bundled PROJ data -> $dest"
done
