#version 330 core

in vec4 vPosition;
layout(location = 0) out vec4 diffuseColor;

void main()
{
    diffuseColor = vPosition;
}
