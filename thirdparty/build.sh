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
    cmake -D BUILD_SHARED_LIBS=ON ..
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
# elif [ "$1" = "openssl" ]; then
#     sudo apt-get install libssl-dev
elif [ "$1" = "all" ]; then
    boost
    yaml_cpp
#     sudo apt-get install libssl-dev
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
# 编译库在yaml-cpp/build/libyaml-cpp.so，libyaml-cpp.so.0.8，libyaml-cpp.so.0.8.0
# 默认安装在
#         头文件/usr/local/include
#         库/usr/local/lib
# 卸载yaml-cpp
# sudo rm -rf /usr/local/include/yaml-cpp
# sudo rm -rf /usr/local/lib/libyaml-cpp*

#openssl
# 默认安装在
#       头文件/usr/include/openssl
#       库/lib/x86_64-linux-gnu/
#         /usr/lib/x86_64-linux-gnu/
# 卸载openssl
# sudo apt-get remove --purge openssl libssl-dev