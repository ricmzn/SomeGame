#include "GL/glew.h"
#include <Base/Exceptions.h>

void glInitializeContext()
{
    // Required for Core contexts
    glewExperimental = GL_TRUE;
    // Try initializing GLEW
    if (glewInit() == GLEW_OK);
    // If it doesn't work, blame the user
    else throw InitializationException(
                "Failed to initialize OpenGL context\n"
                "Try updating your video driver to its latest version");
}
