#pragma once

#include "Transformation.h"

class Rotate : public Transformation {
public:
	Rotate(float angle, glm::vec3 direction);

	glm::mat4 apply() override;

private:
	float angle;
	glm::vec3 direction;
};

