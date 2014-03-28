#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Base/Filesystem/Filesystem.h>
#include "messagebox.h"

int keyPressed[SDL_NUM_SCANCODES] = {0};
int WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;

class Shader
{
    private:
        GLuint vertID, fragID, progID;
        GLuint newShader(GLenum shaderType, const char* source)
        {
            // Tutorial code from http://www.arcsynthesis.org/gltut
            // Copyright © 2012 Jason L. McKesson
            // Variable names changed take custom parameters and work with glLoadGen func_cpp functions
            GLuint shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &source, NULL);
            glCompileShader(shader);
            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (status == false)
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
            vertID = newShader(GL_VERTEX_SHADER, vert.string().c_str());
            fragID = newShader(GL_FRAGMENT_SHADER, frag.string().c_str());

            // Create and link a program
            progID = glCreateProgram();
            glAttachShader(progID, vertID);
            glAttachShader(progID, fragID);
            glLinkProgram(progID);
            glDetachShader(progID, vertID);
            glDetachShader(progID, fragID);
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
            glClearColor(0, 0, 0, 1);
            glClearDepth(1);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CW);
            glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

            // Set up uniforms for the shader
            mvpLocation = glGetUniformLocation(shader.getProgram(), "MVP");
            offsetLocation = glGetUniformLocation(shader.getProgram(), "offset");

            // Generate a VBO and VAO
            glGenBuffers(1, &VBO_id);
            glGenVertexArrays(1, &VAO_id);
            // Bind them
            glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
            glBindVertexArray(VAO_id);
            // Set the buffer data
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
            // Enable the first two vertex attributes
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            // Attribute index, 4 values per position, inform they're floats, unknown, space between values, first value
            glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, 0);
            glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, (void*) (sizeof(vertexData) / 2));
            // And clean up
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        void draw()
        {
            static unsigned totalTime = 0;
            currentFrame = SDL_GetTicks();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            totalTime += deltaTime;

            const float& x = offset.x;
            const float& y = offset.y;
            const float& z = offset.z;
            // Matrices
            model = glm::mat4(1, 0, 0, 0,
                              0, 1, 0, 0,
                              0, 0, 1, 0,
                              x, y, z, 1);

            view = glm::lookAt(glm::vec3(0, 0, 2),
                               glm::vec3(0, 0, 0),
                               glm::vec3(0, 1, 0));

            int sizeX = WINDOW_WIDTH, sizeY = WINDOW_HEIGHT;

            projection = glm::perspective(60.0, (double)sizeX/(double)sizeY, 0.01, 10000.0);

            glm::mat4 modelViewProjection = projection * view * model;

            if (keyPressed[SDL_SCANCODE_LEFT])
            {
                offset.x -= float(deltaTime * 0.001);
            }
            if (keyPressed[SDL_SCANCODE_RIGHT])
            {
                offset.x += float(deltaTime * 0.001);
            }
            if (keyPressed[SDL_SCANCODE_UP])
            {
                offset.y += float(deltaTime * 0.001);
            }
            if (keyPressed[SDL_SCANCODE_DOWN])
            {
                offset.y -= float(deltaTime * 0.001);
            }

            // Set the shader program
            glUseProgram(shader.getProgram());
            glUniformMatrix4fv(mvpLocation, 1, false, &modelViewProjection[0][0]);
            glUniform4fv(offsetLocation, 1, &offset[0]);
            // Bind the vertex array
            glBindVertexArray(VAO_id);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            // Draw the values
            glDrawArrays(GL_TRIANGLES, 0, 36);
            // And unbind the vertex array
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glBindVertexArray(0);
        }
};

int main(int argc, char** argv)
{
    Filesystem::initialize(argc, argv);
    Filesystem::setRootPath("../Data");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_Window* window = SDL_CreateWindow("SomeGame (SDL)",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    glewExperimental = GL_TRUE;
    if (!window || glewInit() != GLEW_OK)
    {
        MessageBoxError("Fatal Error", "Could not initialize an OpenGL context\nMake sure your video drivers are updated");
        fprintf(stderr, "SDL_GetError(): %s\n", SDL_GetError());
        return -1;
    }

    printf("OpenGL version: %s\nDisplay device: %s\nVendor: %s\n",
           glGetString(GL_VERSION),
           glGetString(GL_RENDERER),
           glGetString(GL_VENDOR));

    SDL_ShowWindow(window);
    TestScene Scene;
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

//            if (event.type == SDL_WINDOWEVENT and event.window.event == SDL_WINDOWEVENT_RESIZED)
//            {
//                WINDOW_WIDTH = event.window.data1;
//                WINDOW_HEIGHT = event.window.data2;
//                glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
//            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Scene.draw();
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
