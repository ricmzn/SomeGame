#ifndef TYPES_BINARYTEXTURE_H
#define TYPES_BINARYTEXTURE_H
#include <Engine/Base/Types/Shared.h>

namespace Base {
namespace Types {
class api_public Texture
{
    public:
        // Texture flags
        enum class Flags
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

        static void initialize(Texture* texture);
        static void allocData(Texture* texture);
        static void clearData(Texture* texture);
        static void updateChecksum(Texture* texture);
        static bool isValid(const Texture* texture);
        static void read(Texture* texture, const Byte* src, size_t size);
};
}}

#endif // TYPES_BINARYTEXTURE_H
