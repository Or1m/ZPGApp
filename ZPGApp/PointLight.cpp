#include "PointLight.h"

PointLight::PointLight() : Light(LightType::pointLight) {
	this->position = glm::vec3(0.0, 0.0, 0.0);
	this->constant = 1.0f;
	this->linear = 0.09f;
	this->quadratic = 0.032f;
}

void PointLight::moveTo(glm::vec3 pos) {
	this->position = pos;

	this->notify(*this);
}

void PointLight::move(glm::vec3 trans) {
	this->position += trans;

	this->notify(*this);
}
