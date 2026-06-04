#!/usr/bin/env bash
# Copy the runtime assets INTO each macOS .app bundle so the app is fully
# self-contained.
#
# Why this is needed:
#   On Linux/Windows the assets ship beside the binary in <prefix>/share/assets,
#   and get_asset_dir() finds them relative to the executable. On macOS that
#   sibling layout breaks under Gatekeeper "App Translocation": when a user
#   downloads the DMG and launches a (quarantined, un-notarized) .app, macOS
#   copies the .app ALONE into a random read-only temp dir and runs it from
#   there — with no sibling share/ directory. get_asset_dir() then finds none of
#   its candidate paths and throws, so the GUI aborts immediately on launch.
#
#   get_asset_dir() already checks <App>.app/Contents/share/assets FIRST (it is
#   the executable-relative "../share/assets" candidate), and that path lives
#   inside the bundle, so it survives translocation. Populating it makes the app
#   self-contained with no source change. The CLI keeps using the external
#   share/assets (it is not an .app and is never translocated).
#
# Usage: scripts/macos-bundle-assets.sh <assets-src-dir> <App.app> [App2.app ...]

set -u

ASSETS_SRC="${1:-}"
shift || true

if [ -z "$ASSETS_SRC" ] || [ ! -d "$ASSETS_SRC" ]; then
    echo "ERROR: assets source dir not found: '$ASSETS_SRC'" >&2
    exit 1
fi
[ "$#" -ge 1 ] || { echo "usage: $0 <assets-src-dir> App.app [App2.app ...]" >&2; exit 2; }

for app in "$@"; do
    [ -d "$app" ] || continue
    dest="$app/Contents/share/assets"
    rm -rf "$dest"
    mkdir -p "$app/Contents/share"
    cp -R "$ASSETS_SRC" "$dest"
    echo "    $(basename "$app"): bundled assets -> Contents/share/assets"
done
