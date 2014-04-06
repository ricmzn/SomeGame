SomeGame
========

###Dependencies:

Compiler with C++11 support - GCC 4.6.0 or Visual Studio 2013. MSVC may fail compile at times.  
OpenGL 4.0 - NVIDIA 400 series, AMD 5000 series or Intel HD4000. Anything newer works fine.  
GLEW 1.8 or newer - http://glew.sourceforge.net/  
Latest SDL 2.0 - http://libsdl.org/  
PhysFS 2.0.3 - http://icculus.org/physfs/  
GLM, any version - http://glm.g-truc.net/  
libnoise - http://libnoise.sourceforge.net/index.html *(Tentative)*

###DeveloperTools additional dependencies:

Qt 5.2.0 or newer - http://qt-project.org/  
Probably a stomach for band-aid code

###Notes:

libnoise has a very rudimentary build system which I've been able to rectify with a little bit of CMake-fu. Copy the following to a CMakeLists.txt file in the libnoise source folder and build it as usual.
```cmake
cmake_minimum_required(VERSION 2.8.1)
project(noise)
file(GLOB CPP_LIST "src/*.cpp" "src/model/*.cpp" "src/module/*.cpp")
file(GLOB H_LIST "src/*.h")
file(GLOB H_MODEL_LIST "src/model/*.h")
file(GLOB H_MODULE_LIST "src/module/*.h")
add_library(${PROJECT_NAME} SHARED ${CPP_LIST})

install(FILES ${H_LIST} DESTINATION "include/noise/")
install(FILES ${H_MODEL_LIST} DESTINATION "include/noise/model/")
install(FILES ${H_MODULE_LIST} DESTINATION "include/noise/module/")
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "bin/"
        LIBRARY DESTINATION "lib/")
```
