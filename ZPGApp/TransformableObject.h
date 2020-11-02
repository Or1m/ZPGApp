#pragma once
#include <glm\ext\vector_float3.hpp>

class TransformableObject {
protected:
	TransformableObject();
	virtual ~TransformableObject() {};

	void moveTo(glm::vec3 pos);
	void move(glm::vec3 trans);

	glm::vec3 position;
};

