#!/bin/bash

DIR="linux-build"

if [ ! -d $DIR ]; then
    mkdir $DIR
    cmake -B $DIR -DBLAZE_FETCHCONTENT_BASE_DIR="$(pwd)/linux-deps" $@
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
