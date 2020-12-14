#include "Rotate.h"

Rotate::Rotate(float angle, glm::vec3 direction)
:   angle(angle), direction(direction) { }

glm::mat4 Rotate::apply() {
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(angle), direction);

    return this->modelMatrix;
}