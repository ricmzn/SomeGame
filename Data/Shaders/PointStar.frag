#version 330 core

in float heat;
in float dist;
layout(location = 0) out vec4 diffuseColor;
uniform sampler1D heatTexture;

void main()
{
    diffuseColor = texture(heatTexture, heat) * clamp(pow(dist, 1.6) * 2, 0, 1);
}
