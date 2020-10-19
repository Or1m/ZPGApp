#pragma once
#include <glm\ext\vector_float3.hpp>

#include "ISubject.h"
#include <vector>

class Light {
public:
	Light();
	~Light() {}

	glm::vec3 getLightPosition();
	glm::vec3 getLightColor();

private:
	glm::vec3 lightPosition;
	glm::vec3 lightColor;
};

