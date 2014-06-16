#ifndef BINARYTEXTURE_H
#define BINARYTEXTURE_H
#include <Engine/Base/SharedTypes.h>

/**
 * @brief .
 * Binary as opposed to ASCII, not as in 1 bit-per-pixel
 */
struct BinaryTexture
{
    // Texture flags
    enum Flags
    {
        TEXTURE_1D      = 1,
        TEXTURE_2D      = 2,
        TEXTURE_3D      = 4,
        TEXTURE_RECT    = 8,
        TEXTURE_R       = 16,
        TEXTURE_RG      = 32,
        TEXTURE_RGB     = 64,
        TEXTURE_RGBA    = 128,
        DEFAULT         = TEXTURE_2D | TEXTURE_RGBA
    };

    // Pixel types
    struct R    { uint8_t r; };
    struct RG   { uint8_t r, g; };
    struct RGB  { uint8_t r, g, b; };
    struct RGBA { uint8_t r, g, b, a; };

    // Header (16 bytes)
    struct header_t
    {
        uint8_t magic[3];
        uint8_t version;
        uint16_t width;
        uint16_t height;
        uint16_t depth;
        uint16_t flags;
        char pad[4];
    } header;
    // Data (variable size)
    void* pixels;
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
