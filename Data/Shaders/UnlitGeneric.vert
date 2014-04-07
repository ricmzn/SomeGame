#version 400 core

uniform mat4 projectionMatrix;
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 texCoord;
out vec4 vNormal;
out vec2 vTexCoord;
out vec4 vPosition;

void main(void)
{
    gl_Position = projectionMatrix * position;
    vNormal = normal;
    vTexCoord = texCoord;
    vPosition = position;
}
