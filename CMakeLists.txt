cmake_minimum_required(VERSION 3.22)

project(strumscore)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# TODO: cross platform compilation
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra -Wpedantic -Werror -include cstdint -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -Wextra -Wpedantic -Werror -include cstdint -fdiagnostics-color=always")

set(THIRD_PARTY_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
include(cmake/dependencies.cmake)
include(cmake/options.cmake)

add_subdirectory(src)

if (BUILD_TESTS)
	add_subdirectory(test)
endif()
