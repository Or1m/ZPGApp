#pragma once
#include <glm\ext\vector_float3.hpp>

#include <vector>

#include "Subject.h"
#include "TransformableObject.h"


class Light : public Subject, TransformableObject {
public:
	Light();
	~Light() {}

	void moveTo(glm::vec3 pos);
	void move(glm::vec3 pos);

	glm::vec3 getLightPosition();
	glm::vec3 getLightColor();

private:
	glm::vec3 lightColor;
};

