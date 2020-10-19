#include "Light.h"

Light::Light() 
: lightPosition(glm::vec3(0.0, 0.0, 0.0)), lightColor(1.0, 1.0, 1.0) {}

glm::vec3 Light::getLightPosition() {
	return this->lightPosition;
}

glm::vec3 Light::getLightColor() {
	return this->lightColor;
}