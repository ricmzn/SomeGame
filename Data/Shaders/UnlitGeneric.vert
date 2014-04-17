#version 330 core

uniform mat4 projectionMatrix;
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 normal;
out vec4 vPosition;
out vec2 vTexCoord;
out vec4 vNormal;
out float depth;

void main(void)
{
    gl_Position = projectionMatrix * position;
    vNormal = normal;
    vTexCoord = texCoord;
    vPosition = position;
    depth = gl_Position.z;
}
