find_package(GTest REQUIRED)

enable_testing()

add_executable(cliargs_test
        argument_test.cpp
        any_of_test.cpp
        command_line_test.cpp)

target_link_libraries(cliargs_test
        PRIVATE
            GTest::gtest
            GTest::gtest_main
            cliargs)

add_test(NAME Test COMMAND cliargs_test)