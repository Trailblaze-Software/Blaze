#!/bin/bash

DIR="linux-build"

if [ ! -d $DIR ]; then
    mkdir $DIR
    cmake -B $DIR $@
fi

pushd $DIR || exit
    make -j 8
    cp compile_commands.json ..
    if [ -f "Blaze" ]; then
        cp Blaze ..
    fi
    cp blaze-cli ..
popd || exit
