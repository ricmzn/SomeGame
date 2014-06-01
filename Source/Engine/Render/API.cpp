#include "API.h"
#include <Engine/Base/Exceptions.h>
extern int printf(const char *__format);

void initializeContext()
{
    // Workaround for 3.2+ core contexts
    glewExperimental = GL_TRUE;

    // Try initializing GLEW
    if (glewInit() == GLEW_OK);

    // If it doesn't work, blame the user
    else throw GenericError("Failed to initialize OpenGL context\n"
                            "Try updating your video driver to its latest version");

    // Output some information
    printf("OpenGL version: %s\nDisplay device: %s\nVendor: %s\n\n",
           glGetString(GL_VERSION),
           glGetString(GL_RENDERER),
           glGetString(GL_VENDOR));
}
