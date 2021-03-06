#include "Scale.h"

Scale::Scale(glm::vec3 scale)
:	scale(scale){ }

glm::mat4 Scale::apply() {
	this->modelMatrix = glm::scale(this->modelMatrix, this->scale);

	return this->modelMatrix;
}
