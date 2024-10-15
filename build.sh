#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
    cmake -B build $@
fi

pushd build || exit
    make -j 8
    cp compile_commands.json ..
    cp blaze ..
popd || exit
