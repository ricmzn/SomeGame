#ifndef CAMERA_H
#define CAMERA_H
#include <Engine/Entity/TransformEntity.h>
#include <Engine/Base/SharedTypes.h>

class Camera : public TransformEntity
{
    private:
        Mat4 viewProjectionMatrix;
        float aspectRatio;
        float fieldOfView;
        float nearz, farz;
    public:
        enum class Projection
        {
            Ortho,
            Perspective
        };

        Camera(float vfov, float aspect);
        virtual void spawn(SpawnFlags flags) {(void)flags;}
        virtual void think(float deltaTime);

        void setAspect(float aspect);
        void setClip(float near, float far);
        void setProjection(float vfov, Projection type = Projection::Perspective);
        const glm::mat4& getMatrix() const;
};

#endif // CAMERA_H
