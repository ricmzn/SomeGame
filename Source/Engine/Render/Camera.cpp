#include "Camera.h"
#include <Engine/Entity/TransformEntity.h>
#include <glm/gtc/matrix_transform.hpp>
using namespace Render;

Camera::Camera(float vfov, float aspect, float near, float far)
    : TransformEntity("camera"),
      aspectRatio(aspect),
      fieldOfView(glm::radians(vfov)),
      nearz(near), farz(far),
      perspective(true)
{}

void Camera::spawn()
{}

void Camera::think()
{
    auto pEnt = dynamic_cast<const TransformEntity*>(this->getParent());
    if (pEnt)
    {
        transform.pos = pEnt->transform.pos;
        transform.rot = pEnt->transform.rot;
    }

    Mat4 view, projection;
    view = glm::mat4_cast(transform.rot);
    view = glm::translate(view, -transform.pos);
    if (perspective)
    {
        projection = glm::perspective(fieldOfView, aspectRatio, nearz, farz);
    }
    else
    {
        float halfWidth = fieldOfView / 2;
        float halfHeight = (aspectRatio/fieldOfView) / 2;
        projection = glm::ortho(-halfWidth, halfWidth,
                                -halfHeight, halfHeight,
                                 nearz, farz);
    }

    viewProjectionMatrix = projection * view;
}

void Camera::setClip(float near, float far)
{
    nearz = near;
    farz = far;
}

void Camera::setAspect(float aspect)
{
    aspectRatio = aspect;
}

void Camera::setPerspective(float vfov)
{
    fieldOfView = glm::radians(vfov);
    perspective = true;
}

void Camera::setOrtographic(float width)
{
    fieldOfView = width;
    perspective = false;
}

float Camera::getPerspectiveFov() const
{
    if (perspective)
    {
        return glm::degrees(fieldOfView);
    }
    else
    {
        return 1;
    }
}

const Mat4& Camera::getMatrix() const
{
    return viewProjectionMatrix;
}
