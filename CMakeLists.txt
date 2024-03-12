cmake_minimum_required(VERSION 3.10)

set(vcpkg "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
if(NOT CMAKE_TOOLCHAIN_FILE AND EXISTS "${vcpkg}")
  set(CMAKE_TOOLCHAIN_FILE "${vcpkg}"
      CACHE FILEPATH "CMake toolchain file")
  message(STATUS "vcpkg toolchain found: ${CMAKE_TOOLCHAIN_FILE}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project ("Chip8")

# Add source to this project's executable.
add_executable (Chip8 "src/main.cpp" "src/Chip8.cpp" "include/Chip8.hpp")
# "src/Platform.cpp" "include/Platform.hpp"
find_package(imgui CONFIG REQUIRED)
#find_package(sdl2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
#    "imgui", "sdl2","glad"

target_link_libraries(Chip8 PRIVATE imgui::imgui glad::glad)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Chip8 PROPERTY CXX_STANDARD 20) 
endif()

# TODO: Add tests and install targets if needed.
