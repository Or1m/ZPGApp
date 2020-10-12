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