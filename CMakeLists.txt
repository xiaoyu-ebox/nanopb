#指定CMake版本
cmake_minimum_required(VERSION 3.21)

# 设置项目名称
project(protobuf_test)
# project(Lz4HEnc)

#指定CXX版本
set(CMAKE_CXX_STANDARD 11)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
endif()

include_directories(
    .
    ./proto/
)

# aux_source_directory 查找某路径下的所有源文件，"."表示当前路径
# aux_source_directory(. DIR_TOOT_SRCS)
set(PROTOBUF_TEST_SRC
    pb_common.c
    pb_encode.c
    pb_decode.c
)
aux_source_directory(proto APP_PROTO_SRC)

# set(LZ4HENC_SRC
#     lz4/lz4.c
#     lz4/xxhash.c
# )

# 将变量DIR_TOOT_SRCS中的源文件编译源码生成目标，目标文件名称CMakePro
add_executable(protobuf_test ${PROTOBUF_TEST_SRC} ${APP_PROTO_SRC} main.c)
# add_executable(Lz4HEnc ${LZ4HENC_SRC} mainHEnc.c)
