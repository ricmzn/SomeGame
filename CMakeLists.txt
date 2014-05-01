cmake_minimum_required(VERSION 2.8.11)
project(SomeGame)

set(GNUC_FLAGS "-Wall -Wextra -pedantic -msse -msse2 -mfpmath=sse -g -O3")
add_definitions(-DGLM_FORCE_RADIANS)

set(GAME_NAME ${PROJECT_NAME})
set(TOOLS_NAME DeveloperTools)
set(CMAKE_C_FLAGS "-std=c11 ${GNUC_FLAGS}")
set(CMAKE_CXX_FLAGS "-std=c++11 ${GNUC_FLAGS}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Bin)

option(BUILD_GAME "Build ${GAME_NAME}" ON)
option(BUILD_TOOLS "Build ${TOOLS_NAME}" OFF)
file(GLOB_RECURSE SOURCE_LIST "Source/*.cpp" "Source/*.c" "Source/*.inl" "Source/*.h")

if(BUILD_GAME)
    include_directories("Source")

    if(WIN32)
        set(LIBS mingw32 SDL2main SDL2 glew32 opengl32 physfs)
    else()
        set(LIBS SDL2 GLEW GL physfs)
    endif()

    add_executable(${GAME_NAME} ${SOURCE_LIST} ${MISC_LIST})
    target_link_libraries(${GAME_NAME} ${LIBS})
endif()

if(BUILD_TOOLS)
    file(GLOB_RECURSE SOURCE_LIST "Tools/*.cpp" "Tools/*.h")
    file(GLOB_RECURSE UI_LIST "Tools/*.ui")
    include_directories("Source" "Tools")

    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    find_package(Qt5Widgets)
    find_package(Qt5OpenGL)
    qt5_wrap_ui(UI_HEADERS ${UI_LIST})

    add_executable(${TOOLS_NAME} ${SOURCE_LIST} ${UI_LIST})
    qt5_use_modules(${TOOLS_NAME} Widgets OpenGL)
    if(WIN32)
        target_link_libraries(${TOOLS_NAME} opengl32)
    endif()
endif()

# Non-code files
file(GLOB_RECURSE MISC_LIST "Data/*")
add_custom_target(target SOURCES ${MISC_LIST})
