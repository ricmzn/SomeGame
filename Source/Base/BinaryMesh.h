#ifndef BINARYMESH_H
#define BINARYMESH_H
#include <Base/SharedTypes.h>

struct BinaryMesh
{
    // Header (64 bytes)
    struct header_t {
    // Magic number + version (4 bytes)
    uint8_t magic[3];
    uint8_t version;
    // Counts (60 bytes)
    uint32_t num_indices;
    uint32_t num_verts;
    uint32_t num_uvs;
    uint32_t num_normals;
    uint32_t pad1[11];
    } header;
    // Data (variable size)
    Index* indices;
    Vec4* verts;
    Vec2* uvs;
    Vec4* normals;
    // Verification checksum (4 bytes)
    uint32_t checksum;

    // Static functions (not part of the structure)
    static void initialize(BinaryMesh* mesh);
    static void prepareData(BinaryMesh* mesh);
    static void clearData(BinaryMesh* mesh);
    static void updateChecksum(BinaryMesh* mesh);
    static bool isValid(const BinaryMesh* mesh);
    static void read(BinaryMesh* mesh, const Byte* src, size_t size);
};

#endif // BINARYMESH_H
