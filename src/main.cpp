#include <iostream>
#include "ext/gl_core_3_3.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
            // Variable names changed take custom parameters and work with glLoadGen func_cpp functions
            GLuint shader = gl::CreateShader(shaderType);
            gl::ShaderSource(shader, 1, &source, NULL);
            gl::CompileShader(shader);
            GLint status;
            gl::GetShaderiv(shader, gl::COMPILE_STATUS, &status);
            if (status == gl::FALSE_)
            {
               GLint infoLogLength;
               gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &infoLogLength);

               GLchar *strInfoLog = new GLchar[infoLogLength + 1];
               gl::GetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

               const char *strShaderType = NULL;
               switch(shaderType)
               {
               case gl::VERTEX_SHADER: strShaderType = "vertex"; break;
               case gl::GEOMETRY_SHADER: strShaderType = "geometry"; break;
               case gl::FRAGMENT_SHADER: strShaderType = "fragment"; break;
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
            vertID = createShader(gl::VERTEX_SHADER, vert.string().c_str());
            fragID = createShader(gl::FRAGMENT_SHADER, frag.string().c_str());

            // Create and link a program
            progID = gl::CreateProgram();
            gl::AttachShader(progID, vertID);
            gl::AttachShader(progID, fragID);
            gl::LinkProgram(progID);
            gl::DetachShader(progID, vertID);
            gl::DetachShader(progID, fragID);
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
            gl::ClearColor(0, 0, 0, 1);
            gl::ClearDepth(1);
            gl::Enable(gl::DEPTH_TEST);
            gl::Enable(gl::CULL_FACE);
            gl::CullFace(gl::BACK);
            gl::FrontFace(gl::CW);
            gl::Viewport(0, 0, 1280, 720);

            // Set up uniforms for the shader
            mvpLocation = gl::GetUniformLocation(shader.getProgram(), "MVP");
            offsetLocation = gl::GetUniformLocation(shader.getProgram(), "offset");

            // Generate a VBO and VAO
            gl::GenBuffers(1, &VBO_id);
            gl::GenVertexArrays(1, &VAO_id);
            // Bind them
            gl::BindBuffer(gl::ARRAY_BUFFER, VBO_id);
            gl::BindVertexArray(VAO_id);
            // Set the buffer data
            gl::BufferData(gl::ARRAY_BUFFER, sizeof(vertexData), vertexData, gl::STATIC_DRAW);
            // Enable the first two vertex attributes
            gl::EnableVertexAttribArray(0);
            gl::EnableVertexAttribArray(1);
            // Attribute index, 4 values per position, inform they're floats, unknown, space between values, first value
            gl::VertexAttribPointer(0, 4, gl::FLOAT, gl::FALSE_, 0, 0);
            gl::VertexAttribPointer(1, 4, gl::FLOAT, gl::FALSE_, 0, (void*) (sizeof(vertexData) / 2));
            // And clean up
            gl::DisableVertexAttribArray(0);
            gl::DisableVertexAttribArray(1);
            gl::BindBuffer(gl::ARRAY_BUFFER, 0);
            gl::BindVertexArray(0);
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
            gl::UseProgram(shader.getProgram());
            gl::UniformMatrix4fv(mvpLocation, 1, gl::FALSE_, &modelViewProjection[0][0]);
            gl::Uniform4fv(offsetLocation, 1, &offset[0]);
            // Bind the vertex array
            gl::BindVertexArray(VAO_id);
            gl::EnableVertexAttribArray(0);
            gl::EnableVertexAttribArray(1);
            // Draw the values
            gl::DrawArrays(gl::TRIANGLES, 0, 36);
            // And unbind the vertex array
            gl::DisableVertexAttribArray(0);
            gl::DisableVertexAttribArray(1);
            gl::BindVertexArray(0);
        }
};

void cbfun_windowResized(GLFWwindow* window, int width, int height)
{
    gl::Viewport(0, 0, width, height);
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
    if (Window == nullptr || !gl::sys::LoadFunctions())
    {
        MessageBoxError("Fatal Error", "Could not initialize an OpenGL context\nMake sure your computer supports OpenGL 3.3 and drivers are updated");
        return -1;
    }
    glfwSetWindowSizeCallback(Window, cbfun_windowResized);
    fprintf(stdout, "OpenGL version: %s\nDisplay device: %s\nVendor: %s\n", gl::GetString(gl::VERSION), gl::GetString(gl::RENDERER), gl::GetString(gl::VENDOR));

    TestScene scene;
    bool runGame = true;
    while (runGame)
    {
        glfwPollEvents();
        if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwWindowShouldClose(Window))
        {
            runGame = false;
        }
        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
        scene.draw(Window);
        glfwSwapBuffers(Window);
    }
    glfwDestroyWindow(Window);
    glfwTerminate();
    return 0;
}
