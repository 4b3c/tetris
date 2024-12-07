cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(Main VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find raylib (assumes Homebrew installed raylib)
find_package(raylib REQUIRED)

# Add the executable
add_executable(Main main.cpp)

# Link raylib and system frameworks (macOS-specific)
target_link_libraries(Main PRIVATE raylib)
target_link_libraries(Main PRIVATE "-framework OpenGL -framework Cocoa -framework IOKit")
