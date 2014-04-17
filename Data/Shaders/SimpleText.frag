#version 330 core

in vec2 vTexCoord;
layout(location = 0) out vec4 diffuseColor;
uniform sampler2D textAtlas;

void main(void)
{
    diffuseColor = texture(textAtlas, vTexCoord);
    // Discard bright purple
    if (diffuseColor == vec4(1, 0, 1, 1))
    {
        diffuseColor = vec4(1, 0, 0, 1);
        //discard;
    }
}
