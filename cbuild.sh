#!/bin/bash

# Clean build directory
if [ ! -d ./build ];then
  mkdir build
else
  rm -rf build
  mkdir build
fi

# Remove build artifacts.
if [ -d ./bin];then
  rm -rf bin
fi

# Build project
cd build
cmake ..
make install
