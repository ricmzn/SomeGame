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
        GLuint vertID, fragID, progID;
        GLuint createShader(GLenum shaderType, const char* source)
        {
            // Tutorial code from http://www.arcsynthesis.org/gltut
            // Copyright © 2012 Jason L. McKesson
            // Variable names changed take custom parameters
            GLuint shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &source, NULL);
            glCompileShader(shader);
            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE)
            {
               GLint infoLogLength;
               glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

               GLchar *strInfoLog = new GLchar[infoLogLength + 1];
               glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

               const char *strShaderType = NULL;
               switch(shaderType)
               {
               case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
               case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
               case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
               }

               fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
               delete[] strInfoLog;
            }
            return shader;
        }
    public:
        Shader(const File& vert, const File& frag)
        {
            // Create both shaders
            vertID = createShader(GL_VERTEX_SHADER, vert.string().c_str());
            fragID = createShader(GL_FRAGMENT_SHADER, frag.string().c_str());

            // Create and link a program
            progID = glCreateProgram();
            glAttachShader(progID, vertID);
            glAttachShader(progID, fragID);
            glLinkProgram(progID);
        }
        const int getProgram() {return progID;}
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
            // Set the shader program
            glUseProgram(shader.getProgram());
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

void cbfun_windowResized(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    std::cout << "New window size: " << width << "x" << height << "\n";
}

int main(int argc, char** argv)
{
    PHYSFS_init(argv[0]);
    setRootPath("../Data");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* Window = glfwCreateWindow(1280, 720, "GL App", NULL, NULL);
    glfwSetWindowSizeCallback(Window, cbfun_windowResized);
    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK or Window == nullptr)
    {
        MessageBoxError("Fatal Error", "Could not initialize an OpenGL context\nMake sure your computer supports OpenGL 3.3 and drivers are updated");
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
