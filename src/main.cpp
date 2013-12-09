#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <GL/glu.h>

#ifdef __WIN32__
 #define WIN32_MEAN_AND_LEAN
 #include <windows.h>
#else
 #include <Qt/QMessageBox>
#endif

#include "configfile.h"

class String
{
    private:
        std::string data;
    public:
        String(const char* cstr) : data(cstr) {}
};

class Shader
{
    private:
        int shaderID;
    public:
        Shader(File file) {}
};

int main(int argc, char** argv)
{
    PHYSFS_init(argv[0]);
    setRootPath("../content");
    glfwInit();
    GLFWwindow* Window = glfwCreateWindow(1280, 720, "GL App", 0, 0);
    glfwSwapInterval(1);
    if (!glewInit())
    {
        MessageBoxA(0, "Could not initialize GLEW", "Fatal error", MB_ICONERROR | MB_OK);
        return -1;
    }
    glClearColor(0, 0, 0, 1);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(75, 1280/720, 1, 32768);
    glViewport(0, 0, 1280, 720);
    gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);
    bool runGame = true;
    while (runGame)
    {
        glfwPollEvents();
        if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwWindowShouldClose(Window))
        {
            runGame = false;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(Window);
    }
    glfwDestroyWindow(Window);
    return 0;
}
