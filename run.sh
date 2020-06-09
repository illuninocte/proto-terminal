#!/bin/sh
rm -rf build
mkdir build
cd build
cmake .. > /dev/null
make
cd ..
build/terminal