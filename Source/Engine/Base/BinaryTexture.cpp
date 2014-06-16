#include "BinaryTexture.h"
#include <Engine/Base/NumberGenerator.h>
#include <Engine/Base/Exceptions.h>
#include <cstring>

#define TEXTURE_MAGIC "tex"
#define TEXTURE_VERSION 2

static unsigned getChecksum(const BinaryTexture* texture)
{
    return NumberGenerator::byteSum(&texture->header, sizeof(texture->header));
}

static size_t textureSizeBytes(const BinaryTexture* texture)
{
    if (texture->header.flags & BinaryTexture::Flags::TEXTURE_3D)
    {
        return texture->header.width * texture->header.height * texture->header.height;
    }
    else if (texture->header.flags & BinaryTexture::Flags::TEXTURE_2D ||
             texture->header.flags & BinaryTexture::Flags::TEXTURE_RECT)
    {
        return texture->header.width * texture->header.height;
    }
    else if (texture->header.flags & BinaryTexture::Flags::TEXTURE_1D)
    {
        return texture->header.width;
    }
    else
    {
        throw GenericError("Invalid texture flags");
    }
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
    clearData(texture);

    size_t textureSize = textureSizeBytes(texture);
    if (texture->header.flags & BinaryTexture::Flags::TEXTURE_RGBA)
    {
        texture->pixels = (void*) new BinaryTexture::RGBA[textureSize];
    }
    else if (texture->header.flags & BinaryTexture::Flags::TEXTURE_RGB)
    {
        texture->pixels = (void*) new BinaryTexture::RGB[textureSize];
    }
    else if (texture->header.flags & BinaryTexture::Flags::TEXTURE_RG)
    {
        texture->pixels = (void*) new BinaryTexture::RG[textureSize];
    }
    else if (texture->header.flags & BinaryTexture::Flags::TEXTURE_R)
    {
        texture->pixels = (void*) new BinaryTexture::R[textureSize];
    }
    else
    {
        throw GenericError("Invalid texture flags");
    }
}

void BinaryTexture::clearData(BinaryTexture* texture)
{
    if (texture->pixels)
    {
        if (texture->header.flags & BinaryTexture::Flags::TEXTURE_RGBA)
        {
            delete[] (BinaryTexture::RGBA*)texture->pixels;
        }
        else if (texture->header.flags & BinaryTexture::Flags::TEXTURE_RGB)
        {
            delete[] (BinaryTexture::RGB*)texture->pixels;
        }
        else if (texture->header.flags & BinaryTexture::Flags::TEXTURE_RG)
        {
            delete[] (BinaryTexture::RG*)texture->pixels;
        }
        else if (texture->header.flags & BinaryTexture::Flags::TEXTURE_R)
        {
            delete[] (BinaryTexture::R*)texture->pixels;
        }
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
    memcpy(texture->pixels, src + sizeof(texture->header), textureSizeBytes(texture));
}
