#version 330 core

in float height;
layout(location = 0) out vec4 diffuseColor;

void main()
{
    const vec4 layers[4] = vec4[](
        vec4(0.15, 0.25, 0.95, 1), // Water
        vec4(1,    0.95, 0.25, 1), // Sand
        vec4(0,    0.75, 0.15, 1), // Grass
        vec4(1,    1,    1,    1) // Rock
    );
    const float ranges[4] = float[](
        0,
        0.1,
        0.3,
        0.8
    );

    if (height < ranges[0])
    {
        diffuseColor = layers[0];
    }
    else if (height < ranges[1])
    {
        diffuseColor = mix(layers[0], layers[1], (height-ranges[0])/(ranges[1]-ranges[0]));
    }
    else if (height < ranges[2])
    {
        diffuseColor = mix(layers[1], layers[2], (height-ranges[1])/(ranges[2]-ranges[1]));
    }
    else
    {
        diffuseColor = mix(layers[2], layers[3], (height-ranges[2])/(ranges[3]-ranges[2]));
    }
}
