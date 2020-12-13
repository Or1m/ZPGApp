#pragma once

#include "Light.h"

class SpotLight : public Light {
public:
	SpotLight();
	~SpotLight() { }

	void moveTo(glm::vec3 pos);
	void move(glm::vec3 trans);

	glm::vec3 getLightPosition() { return this->position; }
	void setDirection(glm::vec3 dir);
	glm::vec3 getLightDirection() { return this->direction; }
	float getCutOff()			 { return this->cutOff; }
	glm::vec3 getAttenuation()	 { return glm::vec3(this->constant, this->linear, this->quadratic); }

private:
	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;

	float constant;
	float linear;
	float quadratic;
};

