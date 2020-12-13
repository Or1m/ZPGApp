#include "SpotLight.h"

#include <glm\trigonometric.hpp>

SpotLight::SpotLight() : Light(LightType::spotLight) {
	this->position = glm::vec3(0.0, 0.0, 0.0);
	this->cutOff = glm::cos(glm::radians(20.0f));
	this->direction = glm::vec3(0.0f, -1.0f, 0.0f);

	this->constant = 1.0f;
	this->linear = 0.09f;
	this->quadratic = 0.032f;
}

void SpotLight::moveTo(glm::vec3 pos) {
	this->position = pos;

	this->notify(*this);
}

void SpotLight::move(glm::vec3 trans) {
	this->position += trans;

	this->notify(*this);
}

void SpotLight::setDirection(glm::vec3 dir) {
	this->direction = dir;

	notify(*this);
}