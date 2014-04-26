/**
 * @defgroup NumberGenerator
 */
#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H
#include <cstddef>
#include <cstdint>

namespace NumberGenerator
{
    /**
     * @brief Gets a 32-bit unsigned integer sum of the value of all bytes from data to data+size.
     *
     * While this is a fast checksum function, it's also fairly unreliable.
     * Use with caution, and <i>never</i> use it for hashing.
     * @ingroup NumberGenerator
     */
    uint32_t byteSum(const void* data, size_t size);

    /**
     * @ingroup NumberGenerator
     */
    class PerlinNoise2D
    {
        private:
            int seed;
        public:
            PerlinNoise2D(int seed);
            ~PerlinNoise2D();
            float get(float x, float y) const;
            float operator() (float x, float y) const;
    };
}

#endif // NUMBERGENERATOR_H
