#!/bin/bash
set -e  # Exit on any error

DIR="linux-build"

if [ ! -d $DIR ]; then
    mkdir $DIR
    cmake -B $DIR -DBLAZE_FETCHCONTENT_BASE_DIR="$(pwd)/linux-deps" \
           -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
           -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=mold" \
           $@
fi

pushd $DIR || exit
    make -j 8
    cp compile_commands.json ..
    if [ -f "Blaze" ]; then
        cp Blaze ..
        cp Blaze3D ..
    fi
    cp blaze-cli ..
popd || exit
