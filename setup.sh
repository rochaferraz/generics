#!/bin/sh
git submodule update --init --recursive
cd googletest
cmake .
make
cd ..
mkdir build
cd build
cmake ..
make
cd ..