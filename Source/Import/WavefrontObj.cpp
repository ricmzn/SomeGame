#include "WavefrontObj.h"
#include <cstring>
#include <cstdio>
#include <ctime>
#define MAX_LINE_LENGTH 256

namespace Importers
{
    void WavefrontObj::read(const char* filename)
    {
        clock_t start = clock();
        clock_t delta = clock();
        clock_t taken = 0;
        printf("Loading .obj...\n");
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
                meshData.header.num_faces++;
            }

            // Skip until next line
            while (*fileIterator != '\n')
            {
                fileChar++;
                fileIterator++;
            }
            // Break if we're past the file's size
            if (++fileChar >= meshFile.size()) doCount = false;

            taken += clock() - delta;
            delta = clock();
            if (taken > 2000)
            {
                printf("Still counting...\n");
                fflush(stdout);
                delta = clock();
                taken = 0;
            }
        }
        // Allocate the required space and initialize the counters
        BinaryMesh::prepareData(&meshData);
        unsigned long n_verts = 0, n_normals = 0, n_uvs = 0, n_faces = 0;

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
                meshData.verts[n_verts] = {x, y, z, w};
                n_verts++;
            }
            // Vertex texture coordinate
            else if (sscanf(line, "vt %f %f", &s, &t) >= 2)
            {
                meshData.uvs[n_uvs] = {s, t};
                n_uvs++;
            }
            // Vertex normal
            else if (sscanf(line, "vn %f %f %f %f", &x, &y, &z, &w) >= 3)
            {
                meshData.normals[n_normals] = {x, y, z, w};
                n_normals++;
            }
            // Three-sided face
            else if (sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u",
                            &face.fv[0], &face.ft[0], &face.fn[0],
                            &face.fv[1], &face.ft[1], &face.fn[1],
                            &face.fv[2], &face.ft[2], &face.fn[2]) >= 9)
            {
                meshData.faces[n_faces] = face;
                n_faces++;
            }

            taken += clock() - delta;
            delta = clock();
            if (taken > 2000)
            {
                printf("Still importing...\n");
                fflush(stdout);
                delta = clock();
                taken = 0;
            }
            // EOF
            if (fileChar >= meshFile.size())
            {
                meshFile.close();
            }
        }
        BinaryMesh::updateChecksum(&meshData);
        printf("time taken importing .obj: %ldms", clock() - start);
    }
}
