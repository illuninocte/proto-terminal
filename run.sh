#!/bin/sh
echo "entry_dir = "$HOME"/" > .terminal
# rm -rf build
mkdir build > /dev/null
cd build
cmake .. > /dev/null
make
cd ..
build/terminal