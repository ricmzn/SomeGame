#ifndef API_H
#define API_H

#ifdef __GNUC__
  #ifndef __COUNTER__
    // Work around Qt Creator's function macro auto-completion
    // __GNUC__ is defined during parsing, but __COUNTER__ is not
    // This is some kind of dark magic, but it works
    #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
    #include <GL/glext.h>
  #endif
#endif
#include <GL/glew.h>
#include <string>

/**
 * @brief Loads OpenGL functions in the current context through GLEW
 * @throws InitializationException if glewInit() fails
 */
void initializeContext();

#endif // API_H
