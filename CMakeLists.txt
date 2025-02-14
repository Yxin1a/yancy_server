cmake_minimum_required(VERSION 2.8)#版本
project(yancy_server)#项目名称

include(cmake/utils.cmake)  #引用cmake/utils.cmake(获取文件路径（绝对路径——>相对路径）)      要求：CMakeLists.txt同目录存在cmake文件夹，里面要有utils.cmake文件

set(CMAKE_VERBOSE_MAKEFILE ON)#显示详细的make命令-O0 -ggdb
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++17 -Wall -Wno-deprecated -Wno-unused-function -Wno-builtin-macro-redefined")

include_directories(.)
include_directories(/usr/local/include) #增加yaml-cpp等头文件的路径
link_directories(/usr/local/lib)    #增加yaml-cpp等库文件的路径

set(LIB_SRC #要编译的源码路径
    yancy_server/config.cpp
    yancy_server/fiber.cpp
    yancy_server/log.cpp
    yancy_server/mutex.cpp
    yancy_server/thread.cpp
    yancy_server/util.cpp
    yancy_server/scheduler.cpp
    yancy_server/iomanager.cpp
    yancy_server/timer.cpp
    yancy_server/hook.cpp
    yancy_server/fd_manager.cpp
    yancy_server/address.cpp
    yancy_server/socket.cpp
    yancy_server/bytearray.cpp
    yancy_server/http/http.cpp
    yancy_server/http/http11_parser.rl.cpp
    yancy_server/http/httpclient_parser.rl.cpp
    yancy_server/http/http_parser.cpp
    yancy_server/tcp_server.cpp
    yancy_server/stream.cpp
    yancy_server/streams/socket_stream.cpp
    yancy_server/http/http_session.cpp
    yancy_server/http/http_server.cpp
    yancy_server/http/servlet.cpp
    yancy_server/uri.rl.cpp
    yancy_server/http/http_connection.cpp
    yancy_server/daemon.cpp
    yancy_server/env.cpp
    yancy_server/http/servlet_path.cpp

    yancy_server/application.cpp    #主函数

    )

add_library(yancy_server SHARED ${LIB_SRC})   #加入shared库
force_redefine_file_macro_for_sources(yancy_server)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏
#add_library(yancy_static STATIC ${LIB_SRC})  #建立静态库
#SET_TARGET_PROPERTIES(yancy_static PROPERTIES OUTPUT_NAME "yancy")   #改静态库的库名

find_library(YAMLCPP yaml-cpp)   #用于查找yaml-cpp库。
find_library(PTHREAD pthread)

# find_package(ZLIB REQUIRED) #用于查找zlib库。
# if(ZLIB_FOUND)
#     include_directories(${ZLIB_INCLUDE_DIR})
# endif()

# find_package(OpenSSL REQUIRED)  #用于查找openssl库
# if(OPENSSL_FOUND)
#     include_directories(${OPENSSL_INCLUDE_DIR})
# endif()

set(LIBS #要依赖的库
        yancy_server    #自定义共享库
        pthread #多线程
        yaml-cpp    #yaml-cpp
        # ${ZLIB_LIBRARIES} #zlib库
        # ${OPENSSL_LIBRARIES} #openssl库
        dl  #hook库——libdl 库
    )
    
message("***",${LIBS})   #在日志中记录指定的消息文本

#main
add_executable(server yancy_server/main.cpp) #生成test_log测试文件(可执行文件)
add_dependencies(server yancy_server) #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(server)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(server ${LIBS}) #用于指定链接给定目标和/或其依赖项时要使用的库或标志

#单元测试
#test
add_executable(test_log tests/test_log.cpp) #生成test_log测试文件(可执行文件)
add_dependencies(test_log yancy_server) #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_log)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_log ${LIBS}) #用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_config tests/test_config.cpp)   #生成test_config测试文件(可执行文件)
add_dependencies(test_config yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_config)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_config ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_thread tests/test_thread.cpp)   #生成test_thread测试文件(可执行文件)
add_dependencies(test_thread yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_thread)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_thread ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_util tests/test_util.cpp)   #生成test_util测试文件(可执行文件)
add_dependencies(test_util yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_util)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_util ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_fiber tests/test_fiber.cpp)   #生成test_fiber测试文件(可执行文件)
add_dependencies(test_fiber yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_fiber)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_fiber ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_scheduler tests/test_scheduler.cpp)   #生成test_scheduler测试文件(可执行文件)
add_dependencies(test_scheduler yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_scheduler)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_scheduler ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_iomanager tests/test_iomanager.cpp)   #生成test_iomanager测试文件(可执行文件)
add_dependencies(test_iomanager yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_iomanager)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_iomanager ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_hook tests/test_hook.cpp)   #生成test_hook测试文件(可执行文件)
add_dependencies(test_hook yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_hook)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_hook ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_address tests/test_address.cpp)   #生成test_address测试文件(可执行文件)
add_dependencies(test_address yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_address)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_address ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_socket tests/test_socket.cpp)   #生成test_socket测试文件(可执行文件)
add_dependencies(test_socket yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_socket)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_socket ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_bytearray tests/test_bytearray.cpp)   #生成test_bytearray测试文件(可执行文件)
add_dependencies(test_bytearray yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_bytearray)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_bytearray ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_http tests/test_http.cpp)   #生成test_http测试文件(可执行文件)
add_dependencies(test_http yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_http)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_http ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_http_parser tests/test_http_parser.cpp)   #生成test_http_parser测试文件(可执行文件)
add_dependencies(test_http_parser yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_http_parser)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_http_parser ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_tcp_server tests/test_tcp_server.cpp)   #生成test_tcp_server测试文件(可执行文件)
add_dependencies(test_tcp_server yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_tcp_server)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_tcp_server ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_http_server tests/test_http_server.cpp)   #生成test_http_server测试文件(可执行文件)
add_dependencies(test_http_server yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_http_server)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_http_server ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_uri tests/test_uri.cpp)   #生成test_uri测试文件(可执行文件)
add_dependencies(test_uri yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_uri)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_uri ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_http_connection tests/test_http_connection.cpp)   #生成test_http_connection测试文件(可执行文件)
add_dependencies(test_http_connection yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_http_connection)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_http_connection ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_daemon tests/test_daemon.cpp)   #生成test_daemon测试文件(可执行文件)
add_dependencies(test_daemon yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_daemon)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_daemon ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_env tests/test_env.cpp)   #生成test_env测试文件(可执行文件)
add_dependencies(test_env yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_env)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_env ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

add_executable(test_application tests/test_application.cpp)   #生成test_clientagreement测试文件(可执行文件)
add_dependencies(test_application yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(test_application)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(test_application ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

#examples
add_executable(echo_server examples/echo_server.cpp)   #生成echo_server测试文件(可执行文件)
add_dependencies(echo_server yancy_server)  #测试文件依赖 add_dependencies
force_redefine_file_macro_for_sources(echo_server)    #修改 获取文件路径（绝对路径——>相对路径）   重定义__FILE__宏单元
target_link_libraries(echo_server ${LIBS})#用于指定链接给定目标和/或其依赖项时要使用的库或标志

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)#输出测试文件  的路径yancy-master/bin
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)#输出库的文件路径yancy-master/lib  PROJECT_SOURCE_DIR预定义变量
