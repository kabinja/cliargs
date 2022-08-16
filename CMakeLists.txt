cmake_minimum_required(VERSION 3.22)
project(cliargs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

function(output_conan_include_dirs)
    message(STATUS "INCLUDE DIRS:")
    foreach(DIR ${GTEST_LIBRARY})
        message(STATUS "\t${include_dir_str}${DIR}")
    endforeach()
endfunction()

add_subdirectory(src)
add_subdirectory(test)