project(SomeGame)
cmake_minimum_required(VERSION 2.8)

option(USING_QTCREATOR "Enable to include non-source files in the Qt Creator Project Explorer." OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -pedantic -g")

file(GLOB_RECURSE SOURCE_LIST "src/*.cpp" "src/*.h")
if(QTCREATOR_INTEGRATION)
    message(STATUS "Including non-source files in build. This should not cause any side effects.")
    file(GLOB_RECURSE MISC_LIST "*.cfg" "*.vert" "*.frag")
    add_executable(${PROJECT_NAME} ${SOURCE_LIST} ${MISC_LIST})
else()
    add_executable(${PROJECT_NAME} ${SOURCE_LIST})
endif()

target_link_libraries(${PROJECT_NAME} glfw3 glew32 glu32 opengl32 physfs user32 gdi32)
