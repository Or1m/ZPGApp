#include "Light.h"

Light::Light() 
: lightPosition(glm::vec3(0.0, 0.0, 0.0)), lightColor(1.0, 1.0, 1.0) {}

void Light::moveTo(glm::vec3 pos) {
	this->lightPosition = pos;

	this->notify(*this);
}

void Light::move(glm::vec3 pos) {
	this->lightPosition += pos;

	this->notify(*this);
}

glm::vec3 Light::getLightPosition() {
	return this->lightPosition;
}

glm::vec3 Light::getLightColor() {
	return this->lightColor;
}