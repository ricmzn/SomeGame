#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
smooth out vec4 vertexColor;
uniform vec2 offset;

void main(void)
{
    vec4 vertexOffset = vec4(offset, 0, 0);
    gl_Position = position + vertexOffset;
    vertexColor = color;
}
