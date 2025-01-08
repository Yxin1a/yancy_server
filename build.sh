#!/bin/sh

# 预创建文件夹
BUILD_DIR="./build"

if [ ! -d $BUILD_DIR ]; then
    mkdir $BUILD_DIR    
fi

cd $BUILD_DIR
cmake ..
make -j4