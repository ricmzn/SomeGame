#version 330 core

uniform mat4 matrix;
layout(location = 0) in vec4 position;
out float heat;
out float dist;

void main()
{
    gl_Position = matrix * vec4(position.x, position.y, position.z, 1);
    gl_PointSize = 1024.f / gl_Position.w + 2;

    heat = position.w;
    dist = 4096.f / gl_Position.w;
}
