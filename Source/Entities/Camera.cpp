#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float vfov, float aspect)
    : aspectRatio(aspect),
      fieldOfView(glm::radians(vfov))
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
    Mat4 projection = glm::perspective(fieldOfView, aspectRatio, 0.1f, 1000.f);
    viewProjectionMatrix = projection * view;
}

const glm::mat4& Camera::getMatrix() const
{
    return viewProjectionMatrix;
}
