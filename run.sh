#!/bin/sh
cd build
cmake ..
make
./tatu_tests
cd ..