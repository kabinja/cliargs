find_package(GTest REQUIRED)

enable_testing()

add_executable(cliargs_test
        argument_test.cpp)

output_conan_include_dirs()

target_link_libraries(cliargs_test
        PRIVATE
            GTest::GTest
            cliargs)

add_test(cliargs_gtest cliargs_test)