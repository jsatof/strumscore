cmake_minimum_required(VERSION 3.22)

#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")  for when clang fails to compile test program
project(strumscore)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wpedantic -Wextra -Werror -include cstdint -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -Wpedantic -Wextra -Werror -include cstdint -fdiagnostics-color=always")

#set(THIRD_PARTY_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
#include(cmake/dependencies.cmake)
find_package(JUCE CONFIG REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
