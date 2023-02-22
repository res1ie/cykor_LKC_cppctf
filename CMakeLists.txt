cmake_minimum_required(VERSION 3.26)

project(environment_test)

INCLUDE_DIRECTORIES(C:/Users/user/AppData/Local/Programs/Python/Python310/include)

set(SOURCE_v2 GFv2.cpp matrix.cpp testGFv2.cpp)

add_executable(testv2 ${SOURCE_v2})
add_executable(testpy pymain.cpp)
target_link_libraries(testpy C:/Users/user/AppData/Local/Programs/Python/Python310/libs/python3.lib)
target_link_libraries(testpy C:/Users/user/AppData/Local/Programs/Python/Python310/libs/python310.lib)
