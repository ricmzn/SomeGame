#ifndef SHAREDTYPES_H
#define SHAREDTYPES_H
#include <cstdint>

typedef float lowp;
typedef float mediump;
typedef double highp;
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

#endif // SHAREDTYPES_H
