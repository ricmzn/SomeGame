#ifndef CAMERA_H
#define CAMERA_H
#include <Engine/Entity/TransformEntity.h>
#include <Engine/Base/SharedTypes.h>

namespace Render
{
    class Camera : public TransformEntity
    {
    protected:
        Mat4 viewProjectionMatrix;
        float aspectRatio;
        float fieldOfView;
        float nearz, farz;

    public:
        Camera(float vfov, float aspect);
        virtual void spawn();
        virtual void think();

        void setAspect(float aspect);
        void setClip(float near, float far);
        void setPerspective(float newVerticalFov);
        const Mat4& getMatrix() const;
    };
}

// Camera is an exception to the rule, since it's more of an engine-side entity than a context object
// As such, it's not a bad idea to have it available in the global namespace
using Render::Camera;

#endif // CAMERA_H
