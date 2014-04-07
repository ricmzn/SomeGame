#ifndef BINARYMESH_H
#define BINARYMESH_H
#include <cstdint>

struct BinaryMesh
{
    // Header (4 bytes)
    uint8_t magic[3];
    uint8_t version;
    // Counts (64 bytes)
    uint32_t num_faces;
    uint32_t num_verts;
    uint32_t num_normals;
    uint32_t num_uvs;
    uint32_t pad1[11];
    // Start offsets (64 bytes)
    uint32_t faces;
    uint32_t verts;
    uint32_t normals;
    uint32_t uvs;
    uint32_t pad2[11];
    // Verification checksum (4 bytes)
    uint32_t checksum;

    // Static functions (not part of the structure)
    static void initialize(BinaryMesh* mesh);
    static void updateChecksum(BinaryMesh* mesh);
    static bool isValid(const BinaryMesh* mesh);
};

#endif // BINARYMESH_H
