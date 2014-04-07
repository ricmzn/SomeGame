#include "WavefrontObj.h"
#include <cstring>
#include <cstdio>
#include <ctime>
#define MAX_LINE_LENGTH 256

namespace Importers
{
    void WavefrontObj::read(const char* filename)
    {
        File meshFile(filename);
        unsigned fileChar = 0;
        char line[MAX_LINE_LENGTH];

        // Count elements
        bool doCount = true;
        while (doCount)
        {
            // Working around sscanf
            unsigned iNULL;
            float dNULL;
            // Get a pointer
            const char* fileIterator = &meshFile.data()[fileChar];
            // Vertex coordinates
            if (sscanf(fileIterator, "v %f %f %f %f",
                       &dNULL, &dNULL, &dNULL, &dNULL) >= 3)
            {
                meshData.header.num_verts++;
            }
            // Vertex texture coordinates
            else if (sscanf(fileIterator, "vt %f %f",
                            &dNULL, &dNULL) >= 2)
            {
                meshData.header.num_uvs++;
            }
            // Vertex normals
            else if (sscanf(fileIterator, "vn %f %f %f %f",
                            &dNULL, &dNULL, &dNULL, &dNULL) >= 3)
            {
                meshData.header.num_normals++;
            }
            // Three-sided faces
            else if (sscanf(fileIterator, "f %u/%u/%u %u/%u/%u %u/%u/%u",
                            &iNULL, &iNULL, &iNULL, &iNULL, &iNULL, &iNULL, &iNULL, &iNULL, &iNULL) >= 9)
            {
                meshData.header.num_indices++;
            }

            // Skip until next line
            while (*fileIterator != '\n')
            {
                fileChar++;
                fileIterator++;
            }
            // Break if we're past the file's size
            if (++fileChar >= meshFile.size()) doCount = false;
        }
        // Allocate the required space and initialize the counters
        BinaryMesh::prepareData(&meshData);
        unsigned long verts = 0, normals = 0, uvs = 0,
                v_indices = meshData.header.num_indices*0,
                t_indices = meshData.header.num_indices*1,
                n_indices = meshData.header.num_indices*2;

        // And then parse the file
        fileChar = 0;
        while (meshFile)
        {
            float x, y, z, w = 1;
            float& s = x, t = y;
            Face face;

            // Clear the line buffer
            memset(line, '\0', MAX_LINE_LENGTH-1);
            const char* fileIterator = &meshFile.data()[fileChar];
            unsigned lineChar = 0;
            // Copy the current line to the buffer
            while (*fileIterator != '\n'
                   and lineChar < (MAX_LINE_LENGTH-1)
                   and lineChar + fileChar <= meshFile.size())
            {
                line[lineChar++] = *(fileIterator++);
            }
            fileChar += ++lineChar;

            // Vertex coordinate
            if (sscanf(line, "v %f %f %f %f", &x, &y, &z, &w) >= 3)
            {
                meshData.verts[verts] = {x, y, z, w};
                verts++;
            }
            // Vertex texture coordinate
            else if (sscanf(line, "vt %f %f", &s, &t) >= 2)
            {
                meshData.uvs[uvs] = {t, s};
                uvs++;
            }
            // Vertex normal
            else if (sscanf(line, "vn %f %f %f %f", &x, &y, &z, &w) >= 3)
            {
                meshData.normals[normals] = {x, y, z, w};
                normals++;
            }
            // Three-sided face
            else if (sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u",
                            &face.fv[0], &face.ft[0], &face.fn[0],
                            &face.fv[1], &face.ft[1], &face.fn[1],
                            &face.fv[2], &face.ft[2], &face.fn[2]) >= 9)
            {
                // MASSIVE CODE WALL TODO
                meshData.indices[v_indices].i[0] = face.fv[0]-1;
                meshData.indices[v_indices].i[1] = face.fv[1]-1;
                meshData.indices[v_indices].i[2] = face.fv[2]-1;
                meshData.indices[t_indices].i[0] = face.ft[0]-1;
                meshData.indices[t_indices].i[1] = face.ft[1]-1;
                meshData.indices[t_indices].i[2] = face.ft[2]-1;
                meshData.indices[n_indices].i[0] = face.fn[0]-1;
                meshData.indices[n_indices].i[1] = face.fn[1]-1;
                meshData.indices[n_indices].i[2] = face.fn[2]-1;
                v_indices++; t_indices++; n_indices++;
            }

            // EOF
            if (fileChar >= meshFile.size())
            {
                meshFile.close();
            }
        }
        BinaryMesh::updateChecksum(&meshData);
    }
}
