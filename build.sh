#!/bin/bash

mkdir -p build
pushd build || exit
    cmake ..
    cp compile_commands.json ..
    make -j 8
    cp blaze ..
popd || exit
