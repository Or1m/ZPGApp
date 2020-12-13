#pragma once

#include "Light.h"

class PointLight : public Light {
public:
	PointLight();
	~PointLight() { }

	void moveTo(glm::vec3 pos);
	void move(glm::vec3 trans);

	glm::vec3 getLightPosition() { return this->position; }
	glm::vec3 getAttenuation() { return glm::vec3(this->constant, this->linear, this->quadratic); }

private:
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;
};

