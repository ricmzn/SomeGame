#include "NumberGenerator.h"
#include <glm/gtc/noise.hpp>
#include <cstdlib>
#include <cstdio>
using namespace Base;

PerlinNoise2D::PerlinNoise2D(int seed)
    : seed(seed)
{}

PerlinNoise2D::~PerlinNoise2D() {}
float PerlinNoise2D::get(float x, float y) const
{
    // More interesting, 3D noise flat cut
    return glm::perlin(glm::vec3(x + seed, y + seed, seed/float(RAND_MAX)));

    // Faster, but boring 2D noise
    // return glm::perlin(glm::vec2(x + seed, y + seed));
}
