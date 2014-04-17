#version 330 core

uniform vec2 screenSize = vec2(1024, 600);
uniform vec2 offset;
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
out vec2 vTexCoord;

void main(void)
{
    // Safezone values
    // TODO: pass these in as pre-calculated uniforms
    const float safe_y_mult   = -1.925;
    const float safe_y_offset = 1 - 0.0675;
    const float safe_x_mult   = 1.475;
    const float safe_x_offset = -1;
    float aspect = screenSize.y / screenSize.x;

    vec4 offsetPosition = position
                        + vec4(offset.x * safe_x_mult + safe_x_offset,
                               offset.y * safe_y_mult + safe_y_offset,
                               0, 0);

    vec4 scaledPosition = vec4(offsetPosition.x * aspect, offsetPosition.y, 0, 1);
    gl_Position = scaledPosition;
    vTexCoord = texCoord - 0.0005;
}
