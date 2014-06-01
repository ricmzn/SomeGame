cmake_minimum_required(VERSION 2.8.11)

project(Importer)
file(GLOB_RECURSE SOURCE_LIST "Import/*.cpp" "Import/*.h" "Importer.cpp")
include_directories("../")
add_executable(${PROJECT_NAME} ${SOURCE_LIST})
target_link_libraries(${PROJECT_NAME} Engine assimp)
