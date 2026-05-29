#!/bin/bash
set -e

DIR="macos-build"

# Resolve Homebrew prefixes; fall back gracefully if a formula is missing.
LIBOMP_PREFIX=$(brew --prefix libomp 2>/dev/null || true)
QT_PREFIX=$(brew --prefix qt@6 2>/dev/null || brew --prefix qt6 2>/dev/null || true)

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
    cp -r "$DIR/Blaze.app" .
    cp -r "$DIR/Blaze3D.app" .
fi
