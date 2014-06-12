#include "API.h"
#include <Engine/Base/Exceptions.h>
#include <Engine/System/Messagebox.h>
using namespace Render;

// Declare glLoadGen functions
extern "C" {
    int ogl_LoadFunctions();
    int ogl_GetMinorVersion();
    int ogl_GetMajorVersion();
    int ogl_IsVersionGEQ(int majorVersion, int minorVersion);
}

SDL_GLContext Render::initializeContext(SDL_Window* window, int verMajor, int verMinor)
{
    // Standard settings
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    // Requested OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, verMajor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, verMinor);

    SDL_GLContext context = SDL_GL_CreateContext(window);

    int failedExtensions = ogl_LoadFunctions();

    // Throw away the context if it's not valid
    if (failedExtensions > 0 || !glGetString || !glGetString(GL_RENDERER))
    {
        SDL_GL_DeleteContext(context);
        context = nullptr;
    }
    return context;
}
