#ifndef API_H
#define API_H
#include <SDL2/SDL_video.h>

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

namespace Render
{
    /**
     * @brief Tries to initialize an OpenGL context with the requested version
     * @return a valid context on success, NULL otherwise
     */
    SDL_GLContext initializeContext(SDL_Window* window, int verMajor, int verMinor);
}

#endif // API_H
