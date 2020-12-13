#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light(LightType::directionalLight) {
	this->direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

void DirectionalLight::setDirection(glm::vec3 dir) {
	this->direction = dir;

	notify(*this);
}