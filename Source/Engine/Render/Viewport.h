#ifndef CAMERA_H
#define CAMERA_H
#include <Engine/Base/Types/Shared.h>

namespace Render {
class api_public Viewport
{
    protected:
        Mat4 viewProjectionMatrix;
        float aspectRatio;
        float fieldOfView;
        float nearz, farz;
        bool perspective;

    public:
        Viewport(float vfov, float aspect, float near, float far);
        virtual ~Viewport();
        virtual void spawn();
        virtual void think();

        void setAspect(float aspect);
        void setClip(float near, float far);
        void setPerspective(float vfov);
        void setOrtographic(float width);
        float getPerspectiveFov() const;
        const Mat4& getMatrix() const;
    };
}

#endif // CAMERA_H
