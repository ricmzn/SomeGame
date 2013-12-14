#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <GL/glu.h>
#include "configfile.h"
#include "messagebox.h"

class String
{
    private:
        const char* stringData;
    public:
        String(const char* cstr) : stringData(cstr) {}
        const char* str() const
        {
            return stringData;
        }
};

class Shader
{
    private:
        int shaderID;
    public:
        Shader(File vert, File frag)
        {

        }
};

class VertexCluster
{
    private:
        const float* vertexData;
    public:
        VertexCluster() {}
        VertexCluster(const float* data)
        {
            setData(data);
        }
        void setData(const float* data)
        {
            vertexData = data;
        }
        const float* getData() const
        {
            return vertexData;
        }
};

const float triangle[] = {
    0.0, 0.0, 0.0, 1.f,
    1.0, 0.0, 0.0, 1.f,
    0.5, 1.0, 0.5, 1.f
};

class TestScene
{
    private:
        Shader shader;
        GLuint VBO_id;
    public:
        TestScene() : shader("Shaders/UnlitGeneric.vert", "Shaders/UnlitGeneric.frag")
        {
            glClearColor(0, 0, 0, 1);
            glClearDepth(1);
            glEnable(GL_DEPTH_TEST);
            glShadeModel(GL_SMOOTH);
            glMatrixMode(GL_PROJECTION);
            gluPerspective(75, 1280/720, 1, 32768);
            glViewport(0, 0, 1280, 720);
            gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);

            // Generate a buffer
            glGenBuffers(1, &VBO_id);
            // Bind it
            glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
            // Set its data
            glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
            // And unbind it
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        void draw()
        {
            // Bind the buffer
            glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
            // Enable the first attribute
            glEnableVertexAttribArray(0);
            // Unknown value, 4 values per position, inform they're floats, unknown, space between values, first value
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
            // Draw the values
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
};

int main(int argc, char** argv)
{
    PHYSFS_init(argv[0]);
    setRootPath("../content");
    ConfigTree tree = ParseConfig("default.cfg");
    for (auto& node : tree.nodes)
    {
        std::cout << node->get() << "\n";
    }
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* Window = glfwCreateWindow(1280, 720, "GL App", NULL, NULL);
    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK or Window == nullptr)
    {
        MessageBoxError("Fatal Error", "Could not initialize an OpenGL context");
        return -1;
    }
    TestScene scene;
    bool runGame = true;
    while (runGame)
    {
        glfwPollEvents();
        if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwWindowShouldClose(Window))
        {
            runGame = false;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.draw();
        glfwSwapBuffers(Window);
    }
    glfwDestroyWindow(Window);
    return 0;
}
