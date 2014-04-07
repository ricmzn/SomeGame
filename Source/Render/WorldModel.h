#ifndef WORLDMODEL_H
#define WORLDMODEL_H
#include <Base/BinaryMesh.h>
#include <glm/glm.hpp>

class WorldModel
{
    private:
        void uploadGeometry();
        BinaryMesh meshData;
        glm::mat4 modelMatrix;
    public:
        WorldModel(const BinaryMesh& mesh);
};

#endif // WORLDMODEL_H
