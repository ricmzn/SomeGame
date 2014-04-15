#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float vfov, float aspect)
    : aspectRatio(aspect), position(0, 0, 0)
{
    glm::mat4 view = glm::lookAt(position,
                                 glm::vec3(0, 0, 0),
                                 glm::vec3(0, 1, 0));
    glm::mat4 projection = glm::perspective(vfov, aspect, 0.01f, 1000.f);

    viewProjectionMatrix = projection * view;
}
