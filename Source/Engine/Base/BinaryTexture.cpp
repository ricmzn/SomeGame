#include "BinaryTexture.h"
#include <Engine/Base/NumberGenerator.h>
#include <Engine/Base/Exceptions.h>
#include <cstring>

#define TEXTURE_MAGIC "tex"
#define TEXTURE_VERSION 1

static unsigned getChecksum(const BinaryTexture* texture)
{
    return NumberGenerator::byteSum(&texture->header, sizeof(texture->header));
}

static size_t mipmapSize(const BinaryTexture* texture, unsigned int level)
{
    return (size_t)(texture->header.width * texture->header.height) / pow(2, level);
}

void BinaryTexture::initialize(BinaryTexture* texture)
{
    memset(texture, 0, sizeof(BinaryTexture));
    texture->header.magic[0]    = TEXTURE_MAGIC[0];
    texture->header.magic[1]    = TEXTURE_MAGIC[1];
    texture->header.magic[2]    = TEXTURE_MAGIC[2];
    texture->header.version     = TEXTURE_VERSION;
    texture->pixels             = NULL;
}

void BinaryTexture::allocData(BinaryTexture* texture)
{
    if (texture->pixels) clearData(texture);

    texture->pixels = new uint32_t*[texture->header.levels];
    for (unsigned int level = 0; level < texture->header.levels; level++)
    {
        texture->pixels[level] = new uint32_t[mipmapSize(texture, level)];
    }
}

void BinaryTexture::clearData(BinaryTexture* texture)
{
    if (texture->pixels)
    {
        for (unsigned int level = 0; level < texture->header.levels; level++)
        {
            delete[] texture->pixels[level];
        }
        delete[] texture->pixels;
        texture->pixels = NULL;
    }
}

void BinaryTexture::updateChecksum(BinaryTexture* texture)
{
    texture->checksum = getChecksum(texture);
}

bool BinaryTexture::isValid(const BinaryTexture* texture)
{
    if((texture->header.magic[0] == TEXTURE_MAGIC[0] and
        texture->header.magic[1] == TEXTURE_MAGIC[1] and
        texture->header.magic[2] == TEXTURE_MAGIC[2]) == false)
    return false;

    if (texture->header.version > TEXTURE_VERSION) return false;

    if (getChecksum(texture) != texture->checksum) return false;

    return true;
}

void BinaryTexture::read(BinaryTexture* texture, const Byte* src, size_t size)
{
    texture->header = ((BinaryTexture*)src)->header;
    texture->checksum = *((uint32_t*)(src + size - sizeof(uint32_t)));

    if (texture->header.magic[0] != TEXTURE_MAGIC[0] or
        texture->header.magic[1] != TEXTURE_MAGIC[1] or
        texture->header.magic[2] != TEXTURE_MAGIC[2] or
        texture->header.version > TEXTURE_VERSION)
    {
        initialize(texture);
        throw GenericError("Invalid texture header");
    }
    else if (texture->checksum != NumberGenerator::byteSum(src, size - sizeof(uint32_t)))
    {
        initialize(texture);
        throw GenericError("Invalid texture checksum");
    }

    allocData(texture);
    const void* offset = &texture->pixels[0];
    for (unsigned int level = 0; level < texture->header.levels; level++)
    {
        memcpy(texture->pixels[level], offset, mipmapSize(texture, level));
    }

    if (texture->header.levels > 1)
    {
        fprintf(stderr, "Loading mipmapped textures not yet fully supported, "
                        "overlaying mipmaps instead!\n");
    }
}
