cmake_minimum_required(VERSION 3.22)
project(cliargs)

set(CMAKE_CXX_STANDARD 17)

add_library(cliargs
        src/CommandLine.cpp
        src/Argument.cpp
        src/Argument_p.h
        src/AnyOf.cpp
        src/GroupConstraint.cpp
        src/OneOf.cpp
        src/exceptions.cpp
        src/VisitorUtils.cpp
        src/VisitorUtils.h
        src/Visitor.h)

target_include_directories(cliargs
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include)