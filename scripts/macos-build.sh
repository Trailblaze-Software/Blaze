#!/bin/bash
set -e

DIR="macos-build"

# Resolve Homebrew prefixes; fall back gracefully if a formula is missing.
LIBOMP_PREFIX=$(brew --prefix libomp 2>/dev/null || true)
# Homebrew splits Qt6 across many kegs. Try the split-package keg first
# (qtbase has Qt6Config.cmake); fall back to the monolithic qt@6/qt6 alias
# for older Homebrew setups where Qt ships as a single formula.
QT_PREFIX=$(brew --prefix qtbase 2>/dev/null || brew --prefix qt@6 2>/dev/null || brew --prefix qt6 2>/dev/null || true)

CMAKE_EXTRA=()

if [ -n "$LIBOMP_PREFIX" ]; then
    CMAKE_EXTRA+=(
        "-DOpenMP_CXX_FLAGS=-Xpreprocessor -fopenmp -I${LIBOMP_PREFIX}/include"
        "-DOpenMP_CXX_LIB_NAMES=omp"
        "-DOpenMP_omp_LIBRARY=${LIBOMP_PREFIX}/lib/libomp.dylib"
        "-DOpenMP_C_FLAGS=-Xpreprocessor -fopenmp -I${LIBOMP_PREFIX}/include"
        "-DOpenMP_C_LIB_NAMES=omp"
        "-DOpenMP_C_LIBRARY=${LIBOMP_PREFIX}/lib/libomp.dylib"
    )
fi

if [ -n "$QT_PREFIX" ]; then
    CMAKE_EXTRA+=("-DCMAKE_PREFIX_PATH=${QT_PREFIX}")
fi

if [ ! -d "$DIR" ]; then
    cmake -B "$DIR" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
        "${CMAKE_EXTRA[@]}" \
        "$@"
fi

cmake --build "$DIR" --parallel "$(sysctl -n hw.logicalcpu)"

cp "$DIR/blaze-cli" .
if [ -d "$DIR/Blaze.app" ]; then
    # Remove first in case a previous copy came from a read-only source (e.g. a
    # mounted DMG), which leaves files with 444 permissions that cp can't overwrite.
    rm -rf ./Blaze.app ./Blaze3D.app
    cp -r "$DIR/Blaze.app" .
    cp -r "$DIR/Blaze3D.app" .
fi

# Write qt.conf into each development-build .app so Qt can find its platform
# plugin (libqcocoa.dylib) without needing QT_PLUGIN_PATH in the environment.
# Homebrew's split-package Qt puts plugins in a non-standard per-keg path that
# Qt's compiled-in default search doesn't discover automatically; qt.conf
# overrides the search path for this local build only.
if [ -n "$QT_PREFIX" ]; then
    QT_PLUGINS="$QT_PREFIX/share/qt/plugins"
    [ -d "$QT_PLUGINS" ] || QT_PLUGINS="$QT_PREFIX/plugins"

    for APP in "$DIR/Blaze.app" "$DIR/Blaze3D.app" ./Blaze.app ./Blaze3D.app; do
        [ -d "$APP/Contents/MacOS" ] || continue
        printf '[Paths]\nPlugins = %s\n' "$QT_PLUGINS" > "$APP/Contents/MacOS/qt.conf"
    done
fi
