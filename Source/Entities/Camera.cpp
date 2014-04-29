#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float vfov, float aspect)
    : aspectRatio(aspect),
      fieldOfView(glm::radians(vfov)),
      nearz(0.01f), farz(1000.f)
{}

void Camera::think(float deltaTime)
{
    (void)deltaTime;
    auto pEnt = dynamic_cast<const TransformEntity*>(this->getParent());
    if (pEnt)
    {
        pos = pEnt->pos;
        rot = pEnt->rot;
    }

    Mat4 view;
    view = glm::mat4_cast(rot);
    view = glm::translate(view, -pos);
    Mat4 projection = glm::perspective(fieldOfView, aspectRatio, nearz, farz);
    viewProjectionMatrix = projection * view;
}

void Camera::setClip(float near, float far)
{
    nearz = near;
    farz = far;
}

const glm::mat4& Camera::getMatrix() const
{
    return viewProjectionMatrix;
}
