#version 330 core

in vec4 vPosition;
in vec2 vTexCoord;
in vec4 vNormal;
layout(location = 0) out vec4 diffuseColor;
layout(location = 1) out vec4 normalColor;
uniform sampler2D albedoTexture;

void main()
{
    diffuseColor = texture(albedoTexture, vTexCoord);
    normalColor = vec4(0.5, 0.5, 1, 1);
}
