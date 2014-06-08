#include "API.h"
#include <Engine/Base/Exceptions.h>
#include <Engine/System/Messagebox.h>
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
    int initFailed = ogl_LoadFunctions();

    // Check the validity of the glGetString function pointer (which should always be valid)
    if (!glGetString)
    {
        throw GenericError("glGetString was loaded as a NULL pointer\n"
                           "In other words, shit's broken");
    }

    // Output some information about the renderer
    printf("OpenGL version: %s\nDisplay device: %s\nVendor: %s\n\n",
           glGetString(GL_VERSION),
           glGetString(GL_RENDERER),
           glGetString(GL_VENDOR));

    // If initialization didn't go as planned (eg. some extensions failed), inform the user
    if (initFailed)
    {
        throw GenericError("Failed to initialize OpenGL context\n"
                            "Try updating your video driver to its latest version");
    }
}
