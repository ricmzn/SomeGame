cmake_minimum_required(VERSION 2.8.11)
project(SomeGame)

# Highest warning level, SSE2 enabled, high optimization, debug symbols
set(GNUC_FLAGS "-Wall -Wextra -pedantic -O0 -g3 -fsanitize=undefined")
set(MSVC_FLAGS "/W4 /EHsc /Zi /D_CRT_SECURE_NO_WARNINGS")
# Output everything to the Bin folder
set(OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
# Add some GUI-configurable options
option(BUILD_TOOLS "Enable building of command-line tools. Requires Assimp." OFF)
# Set up compile-time macros
add_definitions(-DGLM_FORCE_RADIANS)

# Find SDL2, PhysFS, GLM and pugixml if on Windows
if(WIN32)
    find_library(lib_SDL2 libSDL2)
    find_library(lib_SDL2main libSDL2main)
    find_library(lib_PhysFS libPhysFS)
    find_library(lib_pugixml libpugixml)
    find_library(lib_ft2 libfreetype)
    find_path(include_SDL2 SDL2/SDL.h)
    find_path(include_PhysFS physfs.h)
    find_path(include_GLM glm/glm.h)
    find_path(include_pugixml pugixml.hpp)
    find_path(include_ft2 freetype.h)
endif()

# Compiler-specific workarounds
if(MSVC)
    add_definitions(-Dand=&& -Dor=|| -Dnot=!)
    set(CMAKE_C_FLAGS "${MSVC_FLAGS}")
    set(CMAKE_CXX_FLAGS "${MSVC_FLAGS}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG    ${OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${OUTPUT_DIRECTORY})
else()
    set(CMAKE_C_FLAGS "-std=c11 ${GNUC_FLAGS}")
    set(CMAKE_CXX_FLAGS "-std=c++11 ${GNUC_FLAGS}")
endif()

# Set up libraries
if(WIN32)
    set(LIBS ${lib_SDL2main} ${lib_SDL2} ${lib_PhysFS} ${lib_pugixml} ${lib_ft2} opengl32)
    include_directories(${include_SDL2} ${include_PhysFS} ${include_GLM} ${include_pugixml} ${include_ft2})
else()
    include_directories("/usr/include/freetype2")
    set(LIBS SDL2 GL physfs pugixml freetype)
endif()

# Engine shared library
add_subdirectory("Source/Engine")

# Various command-line tools
if(BUILD_TOOLS)
    add_subdirectory("Source/Tools")
endif()

# Main executable
#add_subdirectory("Source/Game")

# Add non-code files to the IDE project tree, in case one is used
# Since CMake ignores these, it has no effect on the build
file(GLOB_RECURSE MISC_LIST "Data/*" "Source/*.dox" "*.md")
add_custom_target(target SOURCES ${MISC_LIST})
