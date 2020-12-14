#pragma once

#include "Light.h"

class SpotLight : public Light {
public:
	SpotLight();
	SpotLight(glm::vec3 position);
	SpotLight(glm::vec3 position, glm::vec3 direction);
	SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff);
	SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff, float constant, float linear, float quadratic);
	~SpotLight() { }

	void moveTo(glm::vec3 pos);
	void move(glm::vec3 trans);

	void setDirection(glm::vec3 dir);

	glm::vec3 getLightPosition()	{ return this->position; }
	glm::vec3 getLightDirection()	{ return this->direction; }
	glm::vec3 getAttenuation()		{ return glm::vec3(this->constant, this->linear, this->quadratic); }
	float getCutOff()				{ return this->cutOff; }

private:
	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;

	float constant;
	float linear;
	float quadratic;
};