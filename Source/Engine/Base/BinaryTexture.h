#ifndef BINARYTEXTURE_H
#define BINARYTEXTURE_H
#include <Engine/Base/SharedTypes.h>

/**
 * @brief .
 * Binary as opposed to ASCII, not as in 1 bit-per-pixel
 */
struct BinaryTexture
{
    // Header (16 bytes)
    struct header_t
    {
        uint8_t magic[3];
        uint8_t version;
        uint16_t width;  // Most hardware won't support textures larger
        uint16_t height; // than 65536x65536 in my lifetime, hence 16-bit uints
        uint8_t levels;
        char pad[7];
    } header;
    // Data (variable size)
    uint32_t** pixels;
    // Checksum (4 bytes)
    uint32_t checksum;

    static void initialize(BinaryTexture* texture);
    static void allocData(BinaryTexture* texture);
    static void clearData(BinaryTexture* texture);
    static void updateChecksum(BinaryTexture* texture);
    static bool isValid(const BinaryTexture* texture);
    static void read(BinaryTexture* texture, const Byte* src, size_t size);
};

#endif // BINARYTEXTURE_H
