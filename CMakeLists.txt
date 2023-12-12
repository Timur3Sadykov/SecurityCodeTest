cmake_minimum_required(VERSION 3.26)
project(SecurityCodeTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(SecurityCodeTest main.cpp
        MD5.h
        MD5.cpp
)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test_data/"
)
