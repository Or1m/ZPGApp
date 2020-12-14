#pragma once

#include "Light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight();
	DirectionalLight(glm::vec3 direction);
	~DirectionalLight() { }

	void setDirection(glm::vec3 dir);
	glm::vec3 getLightDirection() { return this->direction; }

private:
	glm::vec3 direction;
};

