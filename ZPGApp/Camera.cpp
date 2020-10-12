#include "Camera.h"

#include <iostream>

Camera* Camera::instance = NULL;

Camera* Camera::getInstance() {
	if (instance == NULL) {
		instance = new Camera();
	}

	return instance;
}

Camera::Camera() {}

Camera::~Camera() {
	delete this;
}

glm::mat4 Camera::getCamera()
{
	return glm::lookAt(this->eye, this->eye + this->target, this->up);
}