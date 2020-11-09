#pragma once

#include <glm/mat4x4.hpp>	
#include <glm/gtc/matrix_transform.hpp>

class Transformation {
public:
	Transformation();
	~Transformation() {}

	virtual glm::mat4 apply() = 0;

protected:
	glm::mat4 modelMatrix;
};

