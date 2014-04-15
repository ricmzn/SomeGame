#version 400 core

in vec4 vPosition;
in vec2 vTexCoord;
in vec4 vNormal;
in float depth;
layout(location = 0) out vec4 diffuseColor;
layout(location = 1) out vec4 normalColor;
uniform sampler2D albedoTexture;
uniform float flatColor;

void main()
{
    float fog = pow(depth, 3)/256;
    vec4 fogColor = vec4(fog, fog, fog, 0);
    if (flatColor == 0.f)
    {
        diffuseColor = texture(albedoTexture, vTexCoord) - fogColor * 0.5;
    }
    else
    {
        diffuseColor = vec4(1, 1, 1, 1) - fogColor;
    }
    //diffuseColor = vec4((vTexCoord.st + 1)/2, 0, 1);
    normalColor = vec4(0.5, 0.5, 1, 1);
}
