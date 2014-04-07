#ifndef SHAREDTYPES_H
#define SHAREDTYPES_H
#include <cstdint>

typedef float mediump;
typedef char Byte;

struct Vec2
{
    mediump x, y;
};

struct Vec3
{
    mediump x, y, z;
};

struct Vec4
{
    mediump x, y, z, w;
};

struct Face
{
    uint32_t fv[3], ft[3], fn[3];
};

struct Index
{
    uint32_t i[3];
};

#endif // SHAREDTYPES_H
