#include "API.h"
#include <Engine/Base/Exceptions.h>
#include <cstdio>

// Declare glLoadGen functions
extern "C" {
    int ogl_LoadFunctions();
    int ogl_GetMinorVersion();
    int ogl_GetMajorVersion();
    int ogl_IsVersionGEQ(int majorVersion, int minorVersion);
}

void initializeContext()
{
    // Try to initialize GL function pointers
    if (ogl_LoadFunctions() == 0);

    // If it doesn't work, blame the user
    else throw GenericError("Failed to initialize OpenGL context\n"
                            "Try updating your video driver to its latest version");

    // Output some information
    printf("OpenGL version: %s\nDisplay device: %s\nVendor: %s\n\n",
           glGetString(GL_VERSION),
           glGetString(GL_RENDERER),
           glGetString(GL_VENDOR));
}
