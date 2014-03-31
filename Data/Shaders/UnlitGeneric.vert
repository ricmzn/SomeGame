#version 400 core

uniform mat4 projectionMatrix;
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
out vec4 vNormal;

void main(void)
{
    gl_Position = projectionMatrix * position;
    vNormal = normal;
}
