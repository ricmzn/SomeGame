#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
smooth out vec4 vertexColor;
uniform mat4 MVP;
uniform vec4 offset;

void main(void)
{
    gl_Position = MVP * (position + offset);
    vertexColor = color;
}
