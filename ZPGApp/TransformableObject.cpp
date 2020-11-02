#include "TransformableObject.h"

TransformableObject::TransformableObject()
:	position(glm::vec3(0.0, 0.0, 0.0)) {}


void TransformableObject::moveTo(glm::vec3 pos) {
	this->position = pos;
}

void TransformableObject::move(glm::vec3 trans) {
	this->position += trans;
}
