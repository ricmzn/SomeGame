#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H
#include <cstddef>

class NumberGenerator
{
    private:
        static long seed;
    public:
        template <typename T> static T byteSum(const void* data, size_t size);
};

template <typename T>
T NumberGenerator::byteSum(const void* data, size_t size)
{
    T sum = 0;
    size_t n = 0;
    while (n < size)
    {
        sum += *((unsigned char*)data + n);
        ++n;
    }
    return sum;
}

#endif // NUMBERGENERATOR_H
