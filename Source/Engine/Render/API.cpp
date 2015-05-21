#include "API.h"
#include <Engine/Base/Exceptions.h>
#include <Engine/System/Messagebox.h>
#include <iostream>

// OpenGL debug message callback
static void errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                          const GLchar* message, const void* userparam)
{
    // Suppress all of the "Unused parameter: foo" warnings
    (void) source;
    (void) type;
    (void) id;
    (void) length;
    (void) userparam;

    if(severity == GL_DEBUG_SEVERITY_HIGH) {
        std::cerr << "HIGH PRIORITY:" << std::endl;
    }
    std::cout << message << std::endl;
}

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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    // Requested OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, verMajor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, verMinor);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    ogl_LoadFunctions();

    // Throw away the context if it's not valid by testing if glGetString was properly loaded
    if(!glGetString || !glGetString(GL_RENDERER)) {
        SDL_GL_DeleteContext(context);
        return nullptr;
    }

    // Set up debug messages if the context supports it
    if(glDebugMessageCallback) {
        glDebugMessageCallback(errorCallback, nullptr);
    }
    else {
        std::cerr << "OpenGL warning: debug output not enabled" << std::endl;
    }

    // Warn the user if querying timers isn't supported
    if(!glQueryCounter) {
        std::cerr << "OpenGL warning: unable to query timers" << std::endl;
    }

    return context;
}
