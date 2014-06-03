#version 330 core

uniform mat4 matrix;
layout(location = 0) in vec4 position;
out vec3 vColor;

void main()
{
    gl_Position = matrix * vec4(position.x, position.y, position.z, 1);
    gl_PointSize = 1024.f / gl_Position.w;

    float color = position.w;
    vColor = vec3(color);
}
