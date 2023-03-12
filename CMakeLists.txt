cmake_minimum_required(VERSION 3.0)

project(initest VERSION 1.0.0.0)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(read1 test_read1.cpp)
add_executable(read2 test_read2.cpp)
