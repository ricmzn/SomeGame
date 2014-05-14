/**
 * @defgroup NumberGenerator
 * @brief Various numeric functions (hashes, checksums, RNGs, etc)
 */
#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H
#include <cstddef>
#include <cstdint>

namespace NumberGenerator
{
    /**
     * @brief Gets a 32-bit unsigned integer sum of the value of all bytes from data to data+size
     * @ingroup NumberGenerator
     */
    uint32_t byteSum(const void* data, size_t size);

    /**
     * @brief A thin wrapper around glm::perlin()
     * @ingroup NumberGenerator
     */
    class PerlinNoise2D
    {
        private:
            int seed;
        public:
            PerlinNoise2D(int seed);
            ~PerlinNoise2D();
            /**
             * @brief Gets a value using 2D perlin, with an offset defined by the random seed
             */
            float get(float x, float y) const;
    };
}

#endif // NUMBERGENERATOR_H
