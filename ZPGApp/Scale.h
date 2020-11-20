#pragma once

#include "Transformation.h"

class Scale : public Transformation {
public:
	Scale(glm::vec3 scale);

	glm::mat4 apply() override;

private:
	glm::vec3 scale;
};