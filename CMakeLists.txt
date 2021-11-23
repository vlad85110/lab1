cmake_minimum_required(VERSION 3.20)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest)

include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)



SET(SOURCE_FILES working\ files/main.cpp)
add_executable(lab1 working\ files/main.cpp "working files/func.h" "working files/func.cpp" "working files/tritset.cpp" "working files/tritproxy.cpp" "working files/trit.h")
target_link_libraries(lab1 gtest gtest_main)
