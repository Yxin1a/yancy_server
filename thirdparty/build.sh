#!/bin/sh
ORIGIN_DIR=$PWD

boost() {
    cd $ORIGIN_DIR/boost_1_87_0
    ./bootstrap.sh
    ./b2
    sudo ./b2 install
}

yaml_cpp() {
    cd $ORIGIN_DIR/yaml-cpp
    mkdir build
    cd build
    cmake ..
    make
    sudo make install
}

if [ -z "$1" ]; then
    echo "usage: build.sh [boost|yaml-cpp|all]"
    exit 1
fi

if [ "$1" = "boost" ]; then
    boost
elif [ "$1" = "yaml-cpp" ]; then
    yaml_cpp
elif [ "$1" = "openssl" ]; then
    sudo apt-get install libssl-dev
elif [ "$1" = "all" ]; then
    boost
    yaml_cpp
else
    echo "usage: build.sh [boost|yaml-cpp|all]"
fi

echo "编译成功"

#boost
# 编译头文件在boost_1_87_0/boost
# 编译库在boost_1_87_0/stage/lib
# 默认安装在
#         头文件/usr/local/include/boost
#         库/usr/local/lib
# 卸载boost
# sudo rm -rf /usr/local/include/boost
# sudo rm -rf /usr/local/lib/libboost*

#yaml-cpp
# 编译头文件在yaml-cpp/include
# 编译库在yaml-cpp/build
# 默认安装在
#         头文件/usr/local/include
#         库/usr/local/lib
# 卸载yaml-cpp
# sudo rm -rf /usr/local/include/yaml-cpp
# sudo rm -rf /usr/local/lib/libyaml-cpp*