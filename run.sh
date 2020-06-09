#!/bin/sh
echo "entry_dir = "$HOME"/" > .terminal
rm -rf build
mkdir build
cd build
cmake .. > /dev/null
make
cd ..
build/terminal