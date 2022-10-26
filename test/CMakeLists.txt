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