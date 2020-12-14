#include "SpotLight.h"

#include <glm\trigonometric.hpp>

SpotLight::SpotLight() : SpotLight(glm::vec3(0.0, 0.0, 0.0)) { }

SpotLight::SpotLight(glm::vec3 position) : SpotLight(position, glm::vec3(0.0f, -1.0f, 0.0f)) { }

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction) : SpotLight(position, direction, 20.0f) { }

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff) : SpotLight(position, direction, cutOff, 1.0f, 0.09f, 0.032f) { }

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff, float constant, float linear, float quadratic) : Light(LightType::spotLight) {
	this->position	= position;
	this->direction = direction;
	this->cutOff	= glm::cos(glm::radians(cutOff));
	

	this->constant	= constant;
	this->linear	= linear;
	this->quadratic = quadratic;
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