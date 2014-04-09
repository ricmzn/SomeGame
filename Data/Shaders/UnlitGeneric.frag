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
    float fogDepth = pow(depth, 3)/256;
    if (flatColor == 0.f)
    {
        diffuseColor = texture(albedoTexture, vTexCoord) - vec3(fogDepth) * 0.5;
    }
    else
    {
        diffuseColor = vec4(1, 1, 1, 1) - vec3(fogDepth);
    }
    //diffuseColor = vec4((vTexCoord.st + 1)/2, 0, 1);
    normalColor = vec4(0.5, 0.5, 1, 1);
}
