#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : DirectionalLight(glm::vec3(0.0f, -1.0f, 0.0f)) { }

DirectionalLight::DirectionalLight(glm::vec3 direction) : Light(LightType::directionalLight) {
	this->direction = direction;
}

void DirectionalLight::setDirection(glm::vec3 dir) {
	this->direction = dir;

	notify(*this);
}