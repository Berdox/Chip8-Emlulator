#cmake_minimum_required(VERSION 3.10)
#project(Chip8)

cmake_minimum_required(VERSION 3.16..3.24)
project(Chip8 VERSION 0.0.1
                    LANGUAGES CXX)


# Set C++ standard to C++14
#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(TESTING "Build Tests" OFF)
option(SOURCE "Build Source" OFF)

# Add libraries
#add_subdirectory("libs/glad")
#add_subdirectory(libs/imgui)
#add_subdirectory(libs/SDL2)

if(SOURCE) 
    # Set source files
    file(GLOB_RECURSE SOURCES "src/*.cpp")

    add_subdirectory(libs/glad)
        # Add the SDL submodule
    add_subdirectory(libs/SDL)
    # Create executable
    add_executable(Chip8 ${SOURCES} ${GLADSOURCE})

    target_include_directories(Chip8 PUBLIC "${PROJECT_SOURCE_DIR}/include" "libs/glad/include/glad" "libs/glad/include/KHR")

    # Link SDL2 libraries to your executable
    target_link_libraries(Chip8 SDL2)

    # Include directories for SDL
    #include_directories(${SDL2_INCLUDE_DIRS})

    # Link SDL libraries
    #target_link_libraries(your_executable_name ${SDL2_LIBRARIES})
endif()

if(TESTING)

    add_subdirectory(libs/googletest)
    # Test executable
    add_executable(testRunner tests/testMain.cpp tests/testChip8.cpp src/Chip8.cpp)

    target_include_directories(testRunner PUBLIC "${PROJECT_SOURCE_DIR}/include")

    target_link_libraries(testRunner gtest_main gmock_main)
endif()





# Link libraries
#target_link_libraries(Chip8 PUBLIC glad)
# imgui googletesting SDL2
