#include "Light.h"
#include <glm\trigonometric.hpp>

static int identificator = 0;

Light::Light() : Light(0) {}

Light::Light(int type)
:	lightColor(glm::vec3(1.0, 1.0, 1.0)), position(glm::vec3(0.0, 0.0, 0.0)), direction(glm::vec3(0.0f, -1.0f, 0.0f)),
	index(identificator++), lightType(type), constant(1.0f), linear(0.09f), quadratic(0.032f), cutOff(glm::cos(glm::radians(15.0f))) {}


void Light::moveTo(glm::vec3 pos) {
	this->position = pos;

	this->notify(*this);
}

void Light::move(glm::vec3 trans) {
	this->position += trans;

	this->notify(*this);
}

void Light::setDirection(glm::vec3 dir) {
	this->direction = dir;

	notify(*this);
}
