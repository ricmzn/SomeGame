#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H
#include <Engine/Base/Types/Shared.h>

namespace Base {
/**
 * @brief Number-generating functions
 */
class api_public NumberGenerator
{
public:
    /**
     * @brief Gets a 32-bit unsigned integer sum of the value of all bytes from data to data+size
     */
    template <typename T>
    static uint32_t byteSum(const T* data, size_t size)
    {
        size_t n = 0;
        uint32_t sum = 0;
        while(n < size) {
            sum += *((unsigned char*)data + n) % UINT32_MAX;
            ++n;
        }
        return sum;
    }

    // Same as above, but automatically guesses the size of T
    template <typename T>
    static uint32_t byteSum(const T data)
    {
        return byteSum(&data, sizeof(data));
    }
};

/**
 * @brief A thin wrapper around glm::perlin()
 */
class api_public PerlinNoise2D
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
