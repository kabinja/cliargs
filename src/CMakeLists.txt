add_library(cliargs "")

target_sources(
        cliargs
        PRIVATE
        AnyOf.cpp
        Argument.cpp
        Argument_p.h
        CommandLine.cpp
        Constraint.cpp
        exceptions.cpp
        GroupConstraint.cpp
        OneOf.cpp
        Parser.cpp
        Parser.h
        validators.h
        validators.cpp
        VisitorUtils.cpp
        VisitorUtils.h
)

target_include_directories(cliargs PUBLIC include)

target_link_libraries(cliargs gcov)

if (CMAKE_COMPILER_IS_GNUCXX)
    include(${CMAKE_BINARY_DIR}/CodeCoverage.cmake)
    append_coverage_compiler_flags()

    # Turn off optimization for non-skewed coverage reports
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
endif()