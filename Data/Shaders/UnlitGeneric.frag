#version 400 core

in vec4 vNormal;
layout(location = 0) out vec4 diffuseColor;
layout(location = 1) out vec4 normalColor;

void main()
{
    diffuseColor = vec4(1, 1, 0, 1);
    normalColor = vec4(0.5, 0.5, 1, 1);
}
