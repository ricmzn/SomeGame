#ifndef WAVEFRONTOBJ_H
#define WAVEFRONTOBJ_H
#include "meshimporter.h"

class WavefrontObj : public MeshImporter
{
    public:
        WavefrontObj() {}
        void import(const File& filename)
        {
            std::stringstream opStream;
            std::string Line;
            glm::vec3 Vec3;
            MeshFace Face;
            while (getline(inData, Line))
            {
                Vec3 = glm::vec3(0, 0, 0);
                switch (Line[0])
                {
                    case 'v': // Vertex
                    {
                        switch (Line[1])
                        {
                            case ' ': // Vertex coordinate
                            {
                                opStream << Line.substr (1, Line.size());
                                opStream >> Vec3.x >> Vec3.y >> Vec3.z;
                                outMesh->vertices.push_back (Vec3);
                                opStream.clear();
                                std::cout << outMesh->vertices.back().x << ' ' << outMesh->vertices.back().y << ' ' << outMesh->vertices.back().z << '\n';
                                break;
                            }
                            case 'n': // Vertex normal
                            {
                                opStream << Line.substr (2, Line.size());
                                opStream >> Vec3.x >> Vec3.y >> Vec3.z;
                                outMesh->normals.push_back (Vec3);
                                opStream.clear();
                                std::cout << outMesh->normals.back().x << ' ' << outMesh->normals.back().y << ' ' << outMesh->normals.back().z << '\n';
                                break;
                            }
                            case 't': // Texture coordinate
                            {
                                opStream << Line.substr (2, Line.size());
                                opStream >> Vec3.x >> Vec3.y;
                                outMesh->uvs.push_back (glm::vec2 (Vec3.x, Vec3.y));
                                opStream.clear();
                                std::cout << outMesh->uvs.back().x << ' ' << outMesh->uvs.back().y << '\n';
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                    case 'f': // Face
                    {
                        sscanf (Line.substr(2, Line.size()).c_str(), "%hu/%hu/%hu %hu/%hu/%hu %hu/%hu/%hu",
                        &Face.v_indices[0], &Face.t_indices[0], &Face.n_indices[0],
                        &Face.v_indices[1], &Face.t_indices[1], &Face.n_indices[1],
                        &Face.v_indices[2], &Face.t_indices[2], &Face.n_indices[2]);
                        outMesh->faces.push_back(Face);
                        std::cout << outMesh->faces.back().v_indices[0] << ' ' << outMesh->faces.back().v_indices[1] << ' ' << outMesh->faces.back().v_indices[2] << '\n';
                        break;
                    }
                    case 's': // Smoothing group
                    {
                        break;
                    }
                    case 'g': // Object
                    {
                        if (Line[Line.size()-1] == '\r')
                            outMesh->sName = Line.substr (2, Line.size()-3);
                        else
                            outMesh->sName = Line.substr (2, Line.size()-2);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
};

#endif // WAVEFRONTOBJ_H
