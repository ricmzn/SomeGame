#version 330 core

uniform mat4 projectionMatrix;
layout(location = 0) in vec4 position;
out float height;

void main()
{
    gl_Position = projectionMatrix * position;
    height = position.y;
}
