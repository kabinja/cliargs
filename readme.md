# CLIArgs

## Build requirements

* CMake 3.22 or higher
* conan 1.51.2 or higher
* C++ 17 or higher

# Building on Windows

## Debug mode

1. move to the build folder
2. run ```conan install .. -s build_type=Debug -s compiler="Visual Studio" -s compiler.runtime=MDd --build=missing```
