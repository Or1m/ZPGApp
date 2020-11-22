#include "Light.h"

static int identificator = 0;

Light::Light() 
:	lightColor(glm::vec3(1.0, 1.0, 1.0)), position(glm::vec3(0.0, 0.0, 0.0)) {
	idx = identificator++;
}


void Light::moveTo(glm::vec3 pos) {
	this->position = pos;

	this->notify(*this);
}

void Light::move(glm::vec3 trans) {
	this->position += trans;

	this->notify(*this);
}

glm::vec3 Light::getLightPosition() {
	return this->position;
}

glm::vec3 Light::getLightColor() {
	return this->lightColor;
}