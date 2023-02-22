cmake_minimum_required(VERSION 3.0)

project(testv2)

set(SOURCE GFv2.cpp matrix.cpp testGFv2.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})