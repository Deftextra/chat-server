#!/bin/bash

if [ ! -d ./build ];then
  mkdir build
else
  if [ -d bin];then
    rm -rf bin
   fi
  rm -rf build
  mkdir build
fi

cd build;
cmake ..
jmake install
