#version 330 core

in float heat;
in float dist;
layout(location = 0) out vec4 diffuseColor;
uniform sampler1D heatTexture;
uniform sampler2D maskTexture;

void main()
{
    // Early discard the smaller stars
    if (dist < 0.15) discard;

    vec4 color = texture(heatTexture, heat) * clamp(pow(dist, 1.6) * 2, 0, 1);
    float mask = texture(maskTexture, gl_PointCoord).r;
    diffuseColor = color * mask;
}
