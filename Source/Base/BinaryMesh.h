#ifndef BINARYMESH_H
#define BINARYMESH_H
#include <Base/SharedTypes.h>
#include <Base/Exceptions.h>

struct BinaryMesh
{
    // Header (64 bytes)
    struct header_t {
    uint8_t magic[3];
    uint8_t version;
    uint32_t nIndices;
    uint32_t nVerts;
    char name[52];
    } header;
    // Data (variable size)
    Vec3* verts;
    Vec2* texCoords;
    Vec3* normals;
    uint32_t* indices;
    // Verification checksum (4 bytes)
    uint32_t checksum;

    // Static functions (not part of the structure)
    static void initialize(BinaryMesh* mesh);
    static void allocData(BinaryMesh* mesh);
    static void clearData(BinaryMesh* mesh);
    static void updateChecksum(BinaryMesh* mesh);
    static bool isValid(const BinaryMesh* mesh);
    static void read(BinaryMesh* mesh, const Byte* src, size_t size);
};

#endif // BINARYMESH_H
