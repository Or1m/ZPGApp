#pragma once

#include <glm/mat4x4.hpp>	
#include <glm/gtc/matrix_transform.hpp>

class Transformation {
public:
	Transformation() : modelMatrix(glm::mat4(1.0)) { }
	~Transformation() { }

	virtual glm::mat4 apply() = 0;

	glm::mat4 getModelMatrix() { return this->modelMatrix; }

protected:
	glm::mat4 modelMatrix;
};

