#include <iostream>
#include <External/gl_core_3_3.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Base/Filesystem/File.h>
#include "messagebox.h"
using namespace gl;

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
        GLuint newShader(GLenum shaderType, const char* source)
        {
            // Tutorial code from http://www.arcsynthesis.org/gltut
            // Copyright © 2012 Jason L. McKesson
            // Variable names changed take custom parameters and work with glLoadGen func_cpp functions
            GLuint shader = CreateShader(shaderType);
            ShaderSource(shader, 1, &source, NULL);
            CompileShader(shader);
            GLint status;
            GetShaderiv(shader, COMPILE_STATUS, &status);
            if (status == FALSE_)
            {
               GLint infoLogLength;
               GetShaderiv(shader, INFO_LOG_LENGTH, &infoLogLength);

               GLchar *strInfoLog = new GLchar[infoLogLength + 1];
               GetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

               const char *strShaderType = NULL;
               switch(shaderType)
               {
               case VERTEX_SHADER: strShaderType = "vertex"; break;
               case GEOMETRY_SHADER: strShaderType = "geometry"; break;
               case FRAGMENT_SHADER: strShaderType = "fragment"; break;
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
            vertID = newShader(VERTEX_SHADER, vert.string().c_str());
            fragID = newShader(FRAGMENT_SHADER, frag.string().c_str());

            // Create and link a program
            progID = CreateProgram();
            AttachShader(progID, vertID);
            AttachShader(progID, fragID);
            LinkProgram(progID);
            DetachShader(progID, vertID);
            DetachShader(progID, fragID);
        }
        const int getProgram() {return progID;}
};

const float triangle[] = {
    // Positions
    -1, -1,  0,  1,
     1, -1,  0,  1,
     0,  1,  0,  1,
    // Colors
     1,  0,  0,  1,
     0,  1,  0,  1,
     0,  0,  1,  1
};

#include "cube.cpp"

class TestScene
{
    private:
        Shader shader;
        GLuint VBO_id;
        GLuint VAO_id;
        GLuint mvpLocation, offsetLocation;
        double deltaTime;
        double currentFrame;
        double lastFrame;

        glm::mat4 model, view, projection;
        glm::vec4 offset;

    public:
        TestScene() : shader("Shaders/UnlitGeneric.vert", "Shaders/UnlitGeneric.frag"), lastFrame(glfwGetTime())
        {
            ClearColor(0, 0, 0, 1);
            ClearDepth(1);
            Enable(DEPTH_TEST);
            Enable(CULL_FACE);
            CullFace(BACK);
            FrontFace(CW);
            Viewport(0, 0, 1280, 720);

            // Set up uniforms for the shader
            mvpLocation = GetUniformLocation(shader.getProgram(), "MVP");
            offsetLocation = GetUniformLocation(shader.getProgram(), "offset");

            // Generate a VBO and VAO
            GenBuffers(1, &VBO_id);
            GenVertexArrays(1, &VAO_id);
            // Bind them
            BindBuffer(ARRAY_BUFFER, VBO_id);
            BindVertexArray(VAO_id);
            // Set the buffer data
            BufferData(ARRAY_BUFFER, sizeof(vertexData), vertexData, STATIC_DRAW);
            // Enable the first two vertex attributes
            EnableVertexAttribArray(0);
            EnableVertexAttribArray(1);
            // Attribute index, 4 values per position, inform they're floats, unknown, space between values, first value
            VertexAttribPointer(0, 4, gl::FLOAT, false, 0, 0);
            VertexAttribPointer(1, 4, gl::FLOAT, false, 0, (void*) (sizeof(vertexData) / 2));
            // And clean up
            DisableVertexAttribArray(0);
            DisableVertexAttribArray(1);
            BindBuffer(ARRAY_BUFFER, 0);
            BindVertexArray(0);
        }
        void draw(GLFWwindow* _window)
        {
            static float totalTime = 0;
            currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            totalTime += deltaTime;

            // Matrices
            model = glm::mat4(1);

            view = glm::lookAt(glm::vec3(0, 0, 2),
                               glm::vec3(0, 0, 0),
                               glm::vec3(0, 1, 0));

            int sizeX, sizeY;
            glfwGetWindowSize(_window, &sizeX, &sizeY);

            projection = glm::perspective(60.0, (double)sizeX/(double)sizeY, 0.01, 10000.0);

            glm::mat4 modelViewProjection = projection * view * model;

            static float modelX = 0, modelY = 0;
            if (glfwGetKey(_window, GLFW_KEY_LEFT))
            {
                modelX -= deltaTime;
            }
            if(glfwGetKey(_window, GLFW_KEY_RIGHT))
            {
                modelX += deltaTime;
            }
            if (glfwGetKey(_window, GLFW_KEY_UP))
            {
                modelY += deltaTime;
            }
            if (glfwGetKey(_window, GLFW_KEY_DOWN))
            {
                modelY -= deltaTime;
            }

            // Offset
            offset.x = modelX;
            offset.y = modelY;
            offset.z = 0;
            offset.w = 1;

            // Set the shader program
            UseProgram(shader.getProgram());
            UniformMatrix4fv(mvpLocation, 1, FALSE_, &modelViewProjection[0][0]);
            Uniform4fv(offsetLocation, 1, &offset[0]);
            // Bind the vertex array
            BindVertexArray(VAO_id);
            EnableVertexAttribArray(0);
            EnableVertexAttribArray(1);
            // Draw the values
            DrawArrays(TRIANGLES, 0, 36);
            // And unbind the vertex array
            DisableVertexAttribArray(0);
            DisableVertexAttribArray(1);
            BindVertexArray(0);
        }
};

void cbfun_windowResized(GLFWwindow* window, int width, int height)
{
    Viewport(0, 0, width, height);
}

int main(int argc, char** argv)
{
    PHYSFS_init(argv[0]);
    setRootPath("../Data");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* Window = glfwCreateWindow(1280, 720, "GL App", NULL, NULL);
    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1);
    if (Window == nullptr || !sys::LoadFunctions())
    {
        MessageBoxError("Fatal Error", "Could not initialize an OpenGL context\nMake sure your computer supports OpenGL 3.3 and drivers are updated");
        return -1;
    }
    glfwSetWindowSizeCallback(Window, cbfun_windowResized);
    fprintf(stdout, "OpenGL version: %s\nDisplay device: %s\nVendor: %s\n", GetString(VERSION), GetString(RENDERER), GetString(VENDOR));

    TestScene scene;
    bool runGame = true;
    while (runGame)
    {
        glfwPollEvents();
        if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwWindowShouldClose(Window))
        {
            runGame = false;
        }
        Clear(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT);
        scene.draw(Window);
        glfwSwapBuffers(Window);
    }
    glfwDestroyWindow(Window);
    glfwTerminate();
    return 0;
}
