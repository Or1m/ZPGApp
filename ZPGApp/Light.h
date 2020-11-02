#pragma once
#include <glm\ext\vector_float3.hpp>

#include "Subject.h"
#include <vector>

class Light : public Subject {
public:
	Light();
	~Light() {}

	void moveTo(glm::vec3 pos);
	void move(glm::vec3 pos);

	glm::vec3 getLightPosition();
	glm::vec3 getLightColor();

private:
	glm::vec3 lightPosition;
	glm::vec3 lightColor;
};

