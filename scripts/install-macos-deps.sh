#!/bin/bash
set -e

# Install Homebrew if not present
if ! command -v brew &>/dev/null; then
    echo "Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

brew install \
    cmake \
    ninja \
    ccache \
    gdal \
    opencv \
    qt@6 \
    libomp \
    openblas \
    lapack
