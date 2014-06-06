#ifndef API_H
#define API_H

#if defined(__GNUC__) && !defined(__COUNTER__)
    // Work around Qt Creator's function macro auto-completion
    // __GNUC__ is defined during parsing, but __COUNTER__ is not
    // This is some kind of dark magic, but it works
    #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
    #include <GL/glext.h>
#else
    // Otherwise, just include the correct header
    #include <Engine/Render/OpenGL/Functions.hpp>
#endif

/**
 * @brief Loads OpenGL functions in the current context
 * @throws InitializationException if it fails
 */
void initializeContext();

#endif // API_H
