#include "NumberGenerator.h"
#include <glm/gtc/noise.hpp>
#include <cstdlib>
#include <cstdio>

namespace NumberGenerator
{
    /*------------------------*/
    /* byteSum(void*, size_t) */
    /*------------------------*/
    uint32_t byteSum(const void* data, size_t size)
    {
        size_t sum = 0;
        size_t n = 0;
        while (n < size)
        {
            sum += *((unsigned char*)data + n);
            ++n;
        }
        return sum;
    }

    /*---------------*/
    /* PerlinNoise2D */
    /*---------------*/
    PerlinNoise2D::PerlinNoise2D(int seed)
        : seed(seed)
    {}

    PerlinNoise2D::~PerlinNoise2D() {}
    float PerlinNoise2D::get(float x, float y) const
    {
        return glm::perlin(glm::vec3(x + seed, y + seed, seed/float(RAND_MAX)));
    }
    float PerlinNoise2D::operator() (float x, float y) const
    {
        return this->get(x, y);
    }
}
