#version 330 core

in vec3 vColor;
layout(location = 0) out vec4 diffuseColor;

void main()
{
    diffuseColor = vec4(vColor.r, vColor.g, vColor.b, 1);
}
