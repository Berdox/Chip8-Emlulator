cmake_minimum_required(VERSION 3.27.7)

project(Chip8_Emulator VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_CXX_COMPILER gcc)
# Sets the build to debug
set(CMAKE_BUILD_TYPE Debug)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
# makes it so gtest is not installed into computer
set(INSTALL_GTEST OFF)

# Add subdirectories
add_subdirectory(src)
#add_subdirectory(libs/googletest)
add_subdirectory(tests)

# Add executable target
add_executable(Chip8_Emulator ${SOURCES})

target_include_directories(Chip8_Emulator PUBLIC include)

# Include directories
#include_directories(include)

