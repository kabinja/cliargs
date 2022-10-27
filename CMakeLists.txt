cmake_minimum_required(VERSION 3.22)
project(cliargs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif()

if(test)
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/CodeCoverage.cmake")
        message(STATUS "Downloading CodeCoverage.cmake from https://github.com/bilke/cmake-modules")
        file(DOWNLOAD "https://raw.githubusercontent.com/bilke/cmake-modules/master/CodeCoverage.cmake"
                "${CMAKE_BINARY_DIR}/CodeCoverage.cmake"
                TLS_VERIFY ON)
    endif()
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES gtest/1.12.1 GENERATORS cmake)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)

if(test)
    enable_testing()
    add_subdirectory(test)
endif()