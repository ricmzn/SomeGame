#include "Viewport.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace Render;

#if 0
Viewport::Viewport(float vfov, float aspect, float near, float far)
    : TransformEntity("camera"),
      aspectRatio(aspect),
      fieldOfView(glm::radians(vfov)),
      nearz(near), farz(far),
      perspective(true)
{}

Viewport::~Viewport()
{}

void Viewport::spawn()
{}

void Viewport::think()
{
    Mat4 view, projection;
    view = glm::mat4_cast(transform.rot);
    view = glm::translate(view, -transform.pos);
    if(perspective) {
        projection = glm::perspective(fieldOfView, aspectRatio, nearz, farz);
    } else {
        float halfWidth = fieldOfView / 2;
        float halfHeight = (aspectRatio/fieldOfView) / 2;
        projection = glm::ortho(-halfWidth, halfWidth,
                                -halfHeight, halfHeight,
                                 nearz, farz);
    }

    viewProjectionMatrix = projection * view;
}

void Viewport::setClip(float near, float far)
{
    nearz = near;
    farz = far;
}

void Viewport::setAspect(float aspect)
{
    aspectRatio = aspect;
}

void Viewport::setPerspective(float vfov)
{
    fieldOfView = glm::radians(vfov);
    perspective = true;
}

void Viewport::setOrtographic(float width)
{
    fieldOfView = width;
    perspective = false;
}

float Viewport::getPerspectiveFov() const
{
    if(perspective) {
        return glm::degrees(fieldOfView);
    } else {
        return 1;
    }
}

const Mat4& Viewport::getMatrix() const
{
    return viewProjectionMatrix;
}
#endif
