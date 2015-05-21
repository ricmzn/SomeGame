#version 330 core

in float heat;
in float dist;
layout(location = 0) out vec4 diffuseColor;
uniform sampler1D heatTexture;
uniform sampler2D maskTexture;

void main()
{
    vec4 color = texture(heatTexture, heat);
    float mask = texture(maskTexture, gl_PointCoord).r;
    diffuseColor = color * mask;
}
