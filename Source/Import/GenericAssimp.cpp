#include "GenericAssimp.h"
#if USE_ASSIMP
#include <cstdio>
#include <cstring>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace Import
{
    void GenericAssimp::read(const char* ospath)
    {
        // Start the import proccess
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(ospath, 0
                                        | aiProcess_Triangulate
                                        | aiProcess_CalcTangentSpace
                                        | aiProcess_JoinIdenticalVertices
                                        | aiProcess_FlipUVs);
        if (!scene or !scene->HasMeshes())
        {
            fprintf(stderr, "%s\n", importer.GetErrorString());
            return;
        }

        const aiMesh* mesh = scene->mMeshes[0];
        meshData.header.nVerts = mesh->mNumVertices;
        meshData.header.nIndices = mesh->mNumFaces * 3;
        BinaryMesh::allocData(&meshData);

        for (unsigned i = 0; i < meshData.header.nIndices; i += 3)
        {
            meshData.indices[i+0] = mesh->mFaces[i/3].mIndices[0];
            meshData.indices[i+1] = mesh->mFaces[i/3].mIndices[1];
            meshData.indices[i+2] = mesh->mFaces[i/3].mIndices[2];
        }
        for (unsigned i = 0; i < meshData.header.nVerts; i++)
        {
            // Vertex positions
            meshData.verts[i].x = mesh->mVertices[i].x;
            meshData.verts[i].y = mesh->mVertices[i].y;
            meshData.verts[i].z = mesh->mVertices[i].z;
            // Texture coordinates
            meshData.texCoords[i].x = mesh->mTextureCoords[0][i].x;
            meshData.texCoords[i].y = mesh->mTextureCoords[0][i].y;
            // Vertex normals
            meshData.normals[i].x = mesh->mNormals[i].x;
            meshData.normals[i].y = mesh->mNormals[i].y;
            meshData.normals[i].z = mesh->mNormals[i].z;
        }

        BinaryMesh::updateChecksum(&meshData);
    }
}
#endif
