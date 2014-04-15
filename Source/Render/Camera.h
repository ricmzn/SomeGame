#ifndef CAMERA_H
#define CAMERA_H
#include <Base/SharedTypes.h>
#include <glm/matrix.hpp>

class Camera
{
    private:
        glm::mat4 viewProjectionMatrix;
        glm::vec3 position;
        float aspectRatio;
        float fieldOfView;
    public:
        enum Projection
        {
            Ortho,
            Perspective
        };

        Camera(float vfov, float aspect);
        void setAspect(float aspect);
        void setPosition(glm::vec3 pos);
        void setProjection(Projection type, float vfov);
        const glm::mat4& getMatrix() const;
};

#endif // CAMERA_H
