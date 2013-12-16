project(SomeGame)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Bin)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -pedantic -g")

file(GLOB_RECURSE SOURCE_LIST "src/*.cpp" "src/*.h")
message(STATUS "Including non-source files in build. This should not cause any side effects.")
file(GLOB_RECURSE MISC_LIST "*.cfg" "*.vert" "*.frag")

add_executable(${PROJECT_NAME} ${SOURCE_LIST} ${MISC_LIST})
target_link_libraries(${PROJECT_NAME} glfw3 opengl32 physfs user32 gdi32)
