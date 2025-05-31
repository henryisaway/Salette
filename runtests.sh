#!/bin/bash

set -e

clear

if [ -d "build" ]; then
    rm -r build
fi

mkdir build

cd build

cmake ..
cmake --build . --target Tests

./Tests