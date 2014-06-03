cmake_minimum_required(VERSION 2.8.11)
project(SomeGame)

# Highest warning level, SSE2 enabled, high optimization, debug symbols
set(GNUC_FLAGS "-Wall -Wextra -pedantic -msse -msse2 -mfpmath=sse -O3 -g")
set(MSVC_FLAGS "/W4 /EHsc /arch:SSE2 /O2 /Zi")
# Output everything to the Bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Bin)
# Set up compile-time macros
add_definitions(-DGLM_FORCE_RADIANS -DGLEW_STATIC)
# Add some GUI-configurable options
option(BUILD_TOOLS "Enable building of command-line tools. Requires Assimp." OFF)

# Compiler-specific workarounds
if(MSVC)
    message(FATAL_ERROR "MSVC builds are currently broken")
    add_definitions(-Dand=&& -Dor=|| -Dnot=!)
    set(CMAKE_C_FLAGS "${MSVC_FLAGS}")
    set(CMAKE_CXX_FLAGS "${MSVC_FLAGS}")
else()
    set(CMAKE_C_FLAGS "-std=c11 ${GNUC_FLAGS}")
    set(CMAKE_CXX_FLAGS "-std=c++11 ${GNUC_FLAGS}")
endif()

# Libraries to link to (which are named differently in Windows)
if(WIN32)
    set(LIBS SDL2main SDL2 opengl32 physfs)
else()
    set(LIBS SDL2 GL physfs)
endif()

# Engine shared library
add_subdirectory("Source/Engine")

# Various command-line tools
if(BUILD_TOOLS)
    add_subdirectory("Source/Tools")
endif()

# Main executable
add_subdirectory("Source/Game")

# Add non-code files to the IDE project tree, in case one is used
# Since CMake ignores these, it has no effect on the build
file(GLOB_RECURSE MISC_LIST "Data/*")
add_custom_target(target SOURCES ${MISC_LIST})
