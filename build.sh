#!/bin/sh

if [ ! -d "./build" ]; then
  mkdir ./build
else
  rm -rf ./build/*
fi

cd build

cmake -DCMAKE_BUILD_TYPE=Debug ..
make

