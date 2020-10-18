#include "Camera.h"

#include <iostream>

Camera* Camera::instance = NULL;

Camera* Camera::getInstance() {
	if (instance == NULL) {
		instance = new Camera();
	}

	return instance;
}

Camera::Camera()
:	projection(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
	eye(glm::vec3(0.0f, 0.0f, -5.0f)), target(glm::vec3(0.0f, 0.0f, 0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)) {}


glm::mat4 Camera::getCamera() {
	// eye, eye + target, up
	return glm::lookAt(this->eye, glm::vec3(0.0f, 0.0f, 0.0f), this->up);

	/*return glm::lookAt(	glm::vec3(0.0f, 0.0f, -5.0f),
							glm::vec3(0.0f, 0.0f, 0.0f),
							glm::vec3(0.0f, 1.0f, 0.0f));*/
}

glm::mat4 Camera::getProjection() {
	return this->projection;
}

void Camera::toFront() {
	//this->eye += glm::normalize(this->target);

	this->notify();
}

void Camera::toLeft() {
	this->eye += glm::normalize(glm::cross(this->target, this->up));

	this->notify();
}

void Camera::toBack() {
	this->eye.z -= 0.05f;

	this->notify();
}

void Camera::toRight() {
	//this->eye += glm::normalize(glm::cross(this->target, this->up));

	this->notify();
}

// Observer
void Camera::attach(IObserver* observer) {
	this->observers.push_back(observer);
}

void Camera::detach(IObserver* observer) {
	auto iterator = std::find(observers.begin(), observers.end(), observer);

	if (iterator != observers.end())
		observers.erase(iterator);
}

void Camera::notify() {
	for (IObserver* observer : observers)
		observer->update(this->getCamera());
}