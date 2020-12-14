#include "PointLight.h"

PointLight::PointLight() : PointLight(glm::vec3(0.0, 0.0, 0.0)) { }

PointLight::PointLight(glm::vec3 position) : PointLight(position, 1.0f, 0.09f, 0.032f) { }

PointLight::PointLight(glm::vec3 position, float constant, float linear, float quadratic) : Light(LightType::pointLight) {
	this->position	= position;
	this->constant	= constant;
	this->linear	= linear;
	this->quadratic = quadratic;
}

void PointLight::moveTo(glm::vec3 pos) {
	this->position = pos;

	this->notify(*this);
}

void PointLight::move(glm::vec3 trans) {
	this->position += trans;

	this->notify(*this);
}
