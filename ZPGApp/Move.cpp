#include "Move.h"

Move::Move(glm::vec3 pos) {
    this->position = pos;
}

glm::mat4 Move::apply() {
    this->modelMatrix = glm::translate(this->modelMatrix, this->position);
    
    return this->modelMatrix;
}
