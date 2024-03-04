#cmake_minimum_required(VERSION 3.10)
#project(Chip8)

cmake_minimum_required(VERSION 3.16..3.24)
project(Chip8 VERSION 0.0.1
                    LANGUAGES CXX)


# Set C++ standard to C++14
#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Set include directories
#include_directories(SYSTEM "include")

# Add libraries
#add_subdirectory("libs/glad")
#add_subdirectory(libs/imgui)
add_subdirectory(libs/googletest)
#add_subdirectory(libs/SDL2)

# Create executable
add_executable(Chip8 ${SOURCES})

target_include_directories(Chip8 PUBLIC "${PROJECT_SOURCE_DIR}/include")


# Test executable
add_executable(testRunner tests/testMain.cpp tests/testChip8.cpp)

target_include_directories(testRunner PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(testRunner gtest_main gmock_main)

# Link libraries
#target_link_libraries(Chip8 PUBLIC glad)
# imgui googletesting SDL2
