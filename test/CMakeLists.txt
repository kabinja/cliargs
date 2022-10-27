find_package(GTest REQUIRED)

add_executable(cliargs_test
        any_of_test.cpp
        argument_test.cpp
        command_line_test.cpp
        one_of_test.cpp)

target_link_libraries(cliargs_test
        PRIVATE
            GTest::gtest
            GTest::gtest_main
            cliargs)

gtest_discover_tests(cliargs_test)
if (CMAKE_COMPILER_IS_GNUCXX)
    include(${CMAKE_BINARY_DIR}/CodeCoverage.cmake)

    # optional excludes - None needed here
    #    set(COVERAGE_EXCLUDES)

    setup_target_for_coverage_gcovr_xml(
            NAME CoverageXml
            EXECUTABLE cliargs_test
            DEPENDENCIES cliargs
    )
    setup_target_for_coverage_gcovr_html(
            NAME CoverageHtml
            EXECUTABLE cliargs_test
            DEPENDENCIES cliargs
    )
    #setup_target_for_coverage_lcov(
    #        NAME CoverageLcov
    #        EXECUTABLE cliargs_test
    #        DEPENDENCIES cliargs_test cliargs
    #)
endif ()