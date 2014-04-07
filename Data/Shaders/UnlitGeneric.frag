#version 400 core

in vec4 vNormal;
in vec2 vTexCoord;
in vec4 vPosition;
layout(location = 0) out vec4 diffuseColor;
layout(location = 1) out vec4 normalColor;
uniform sampler2D albedoTexture;

void main()
{
    diffuseColor = texture(albedoTexture, vTexCoord);
    //diffuseColor = vec4(vTexCoord.st, 0, 1);
    normalColor = vec4(0.5, 0.5, 1, 1);
}
