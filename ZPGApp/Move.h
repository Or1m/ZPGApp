#pragma once
#include "Transformation.h"
class Move : public Transformation {
public:
	Move(glm::vec3 pos);

	glm::mat4 apply() override;

private:
	glm::vec3 position;
};