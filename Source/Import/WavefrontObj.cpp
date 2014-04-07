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
            int iNULL;
            double dNULL;
            // Get a pointer
            const char* fileIterator = &meshFile.data()[fileChar];
            // Vertex coordinates
            if (sscanf(fileIterator, "v %lf %lf %lf %lf",
                       &dNULL, &dNULL, &dNULL, &dNULL) >= 3)
            {
                meshData.num_verts++;
            }
            // Vertex normals
            else if (sscanf(fileIterator, "vn %lf %lf %lf %lf",
                            &dNULL, &dNULL, &dNULL, &dNULL) >= 3)
            {
                meshData.num_normals++;
            }
            // Vertex texture coordinates
            else if (sscanf(fileIterator, "vt %lf %lf",
                            &dNULL, &dNULL) >= 2)
            {
                meshData.num_uvs++;
            }
            // Three-sided faces
            else if (sscanf(fileIterator, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                            &iNULL, &iNULL, &iNULL, &iNULL, &iNULL, &iNULL, &iNULL, &iNULL, &iNULL) >= 9)
            {
                meshData.num_faces++;
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

        // And then parse the file
        fileChar = 0;
        while (meshFile)
        {
            double x, y, z, w = 1;
            double& s = x, t = y;

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
            if (sscanf(line, "v %lf %lf %lf %lf", &x, &y, &z, &w) >= 3)
            {

            }
            // Vertex normal
            else if (sscanf(line, "vn %lf %lf %lf %lf", &x, &y, &z, &w) >= 3)
            {

            }
            // Vertex texture coordinate
            else if (sscanf(line, "vt %lf %lf", &s, &t) >= 2)
            {

            }
            // Three-sided face
            else if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                            &x, &y, &z,
                            &x, &y, &z,
                            &x, &y, &z))
            {

            }

            // EOF
            if (fileChar >= meshFile.size())
            {
                meshFile.close();
            }
            BinaryMesh::updateChecksum(&meshData);
        }
    }
}
