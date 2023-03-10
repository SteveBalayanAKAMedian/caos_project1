cmake_minimum_required(VERSION 3.10)

project(divmod)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(SRCS ${SRC_DIR}/test_default.c ${SRC_DIR}/divmod.c)

add_executable(divmod ${SRCS})

set_target_properties(divmod PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
