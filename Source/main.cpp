#include <iostream>
#include <External/gl_core_3_3.hpp>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Base/Filesystem/File.h>
#include "messagebox.h"

int keyPressed[SDL_NUM_SCANCODES] = {0};
int WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;

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
            GLuint shader = gl::CreateShader(shaderType);
            gl::ShaderSource(shader, 1, &source, NULL);
            gl::CompileShader(shader);
            GLint status;
            gl::GetShaderiv(shader, gl::COMPILE_STATUS, &status);
            if (status == false)
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
            vertID = newShader(gl::VERTEX_SHADER, vert.string().c_str());
            fragID = newShader(gl::FRAGMENT_SHADER, frag.string().c_str());

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
        unsigned deltaTime;
        unsigned currentFrame;
        unsigned lastFrame;

        glm::mat4 model, view, projection;
        glm::vec4 offset;

    public:
        TestScene() : shader("Shaders/UnlitGeneric.vert", "Shaders/UnlitGeneric.frag"), lastFrame(SDL_GetTicks())
        {
            gl::ClearColor(0, 0, 0, 1);
            gl::ClearDepth(1);
            gl::Enable(gl::DEPTH_TEST);
            gl::Enable(gl::CULL_FACE);
            gl::CullFace(gl::BACK);
            gl::FrontFace(gl::CW);
            gl::Viewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

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
            gl::VertexAttribPointer(0, 4, gl::FLOAT, false, 0, 0);
            gl::VertexAttribPointer(1, 4, gl::FLOAT, false, 0, (void*) (sizeof(vertexData) / 2));
            // And clean up
            gl::DisableVertexAttribArray(0);
            gl::DisableVertexAttribArray(1);
            gl::BindBuffer(gl::ARRAY_BUFFER, 0);
            gl::BindVertexArray(0);
        }
        void draw()
        {
            static unsigned totalTime = 0;
            currentFrame = SDL_GetTicks();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            totalTime += deltaTime;

            // Matrices
            model = glm::mat4(1);

            view = glm::lookAt(glm::vec3(0, 0, 2),
                               glm::vec3(0, 0, 0),
                               glm::vec3(0, 1, 0));

            int sizeX = WINDOW_WIDTH, sizeY = WINDOW_HEIGHT;

            projection = glm::perspective(60.0, (double)sizeX/(double)sizeY, 0.01, 10000.0);

            glm::mat4 modelViewProjection = projection * view * model;

            static float modelX = 0, modelY = 0;
            if (keyPressed[SDL_SCANCODE_LEFT])
            {
                modelX -= float(deltaTime * 0.001);
            }
            if (keyPressed[SDL_SCANCODE_RIGHT])
            {
                modelX += float(deltaTime * 0.001);
            }
            if (keyPressed[SDL_SCANCODE_UP])
            {
                modelY += float(deltaTime * 0.001);
            }
            if (keyPressed[SDL_SCANCODE_DOWN])
            {
                modelY -= float(deltaTime * 0.001);
            }

            // Offset
            offset.x = modelX;
            offset.y = modelY;
            offset.z = 0;
            offset.w = 1;

            // Set the shader program
            gl::UseProgram(shader.getProgram());
            gl::UniformMatrix4fv(mvpLocation, 1, false, &modelViewProjection[0][0]);
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

int main(int argc, char** argv)
{
    PHYSFS_init(argv[0]);
    setRootPath("../Data");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SomeGame (SDL)",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    if (!window || !gl::sys::LoadFunctions())
    {
        MessageBoxError("Fatal Error", "Could not initialize an OpenGL context\nMake sure your video drivers are updated");
        fprintf(stderr, "SDL_GetError(): %s\n", SDL_GetError());
        return -1;
    }

    printf("OpenGL version: %s\nDisplay device: %s\nVendor: %s\n",
           gl::GetString(gl::VERSION),
           gl::GetString(gl::RENDERER),
           gl::GetString(gl::VENDOR));

    TestScene scene;
    bool runGame = true;
    while (runGame)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                keyPressed[event.key.keysym.scancode] = 1;
            }
            else if (event.type == SDL_KEYUP)
            {
                keyPressed[event.key.keysym.scancode] = 0;
            }

            if (event.type == SDL_QUIT or event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                runGame = false;
            }

            if (event.type == SDL_WINDOWEVENT and event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                WINDOW_WIDTH = event.window.data1;
                WINDOW_HEIGHT = event.window.data2;
                gl::Viewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
            }
        }
        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
        scene.draw();
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
