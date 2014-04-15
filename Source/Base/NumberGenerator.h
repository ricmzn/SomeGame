#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H
#include <cstddef>
#include <cstdlib>
#include <ctime>

namespace NumberGenerator
{
    /*--------------*/
    /* Declarations */
    /*--------------*/
    template <typename T> T byteSum(const void* data, size_t size);

    /*-----------------*/
    /* Implementations */
    /*-----------------*/
    template <typename T>
    T byteSum(const void* data, size_t size)
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
}

#endif // NUMBERGENERATOR_H
