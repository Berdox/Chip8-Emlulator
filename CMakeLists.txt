cmake_minimum_required(VERSION 3.14)

set(vcpkg "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
if(NOT CMAKE_TOOLCHAIN_FILE AND EXISTS "${vcpkg}")
  set(CMAKE_TOOLCHAIN_FILE "${vcpkg}"
      CACHE FILEPATH "CMake toolchain file")
  message(STATUS "vcpkg toolchain found: ${CMAKE_TOOLCHAIN_FILE}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project ("Chip8")

#[==[
# Define a testing option
option(TESTING "Enable testing" OFF)


if(TESTING)
    # Enable testing
    enable_testing()
    message(STATUS "Testing enabled.")

        # Add source files to the executable
    add_executable(Chip8 
        "src/main.cpp"
        "src/Chip8.cpp"
        "src/Platform.cpp"
        "include/Chip8.hpp"
        "include/Platform.hpp"
        "tests/testChip8.cpp"
        "tests/testMain.cpp"
    )

    # Find required packages
    find_package(imgui CONFIG REQUIRED)
    find_package(sdl2 CONFIG REQUIRED)
    find_package(glad CONFIG REQUIRED)
    find_package(GTest CONFIG REQUIRED)

    # Link libraries to the executable
    target_link_libraries(Chip8 PRIVATE imgui::imgui glad::glad GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

else()
    message(STATUS "Building Chip8 without testing.")

    # Add source files to the executable
    add_executable(Chip8 
        "src/main.cpp"
        "src/Chip8.cpp"
        "src/Platform.cpp"
        "include/Chip8.hpp"
        "include/Platform.hpp"
    )

    # Find required packages
    find_package(imgui CONFIG REQUIRED)
    find_package(sdl2 CONFIG REQUIRED)
    find_package(glad CONFIG REQUIRED)
    find_package(glfw3 CONFIG REQUIRED)

    # Link libraries to the executable
    target_link_libraries(Chip8 PRIVATE imgui::imgui glad::glad SDL2::SDL2main SDL2::SDL2 glfw)

    # Add include directories
    target_include_directories(Chip8 PRIVATE include)
endif()
]==]

cmake_minimum_required(VERSION 3.14)
project(Chip8)

# Define a testing option
option(TESTING "Enable testing" OFF)

# Common source files
set(SOURCES
    "src/Chip8.cpp"
    #"src/Platform.cpp"
    "include/Chip8.hpp"
    #"include/Platform.hpp"
)

# Add tests if testing is enabled
if(TESTING)
    enable_testing()
    message(STATUS "Testing enabled.")
    
    # Add test-specific sources
    list(APPEND SOURCES 
        "tests/testChip8.cpp"
        "tests/testMain.cpp"
    )

    # Find Google Test
    find_package(GTest CONFIG REQUIRED)
else()
    list(APPEND SOURCES 
        "src/main.cpp"
    )
endif()

# Create the executable
add_executable(Chip8 ${SOURCES})

# Find required packages
find_package(imgui CONFIG REQUIRED)
find_package(sdl2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# Link common libraries
target_link_libraries(Chip8 PRIVATE imgui::imgui glad::glad)

if(TESTING)
    target_link_libraries(Chip8 PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
else()
    target_link_libraries(Chip8 PRIVATE SDL2::SDL2main SDL2::SDL2 glfw)
endif()

# Add include directories
target_include_directories(Chip8 PRIVATE include)

if (CMAKE_VERSION VERSION_GREATER 3.12) 
  set_property(TARGET Chip8 PROPERTY CXX_STANDARD 20) 
endif()

# TODO: Add tests and install targets if needed.
