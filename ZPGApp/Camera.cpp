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
	eye(glm::vec3(0.0f, 0.0f, 3.0f)), target(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
	cameraSpeed(3.5f), deltaTime(0.015f), sensitivity(0.1f), yaw(-89.0f), pitch(0.0f), lastX(400), lastY(300), firstTimeMouse(true) {}


glm::mat4 Camera::getCamera() {
	return glm::lookAt(this->eye, this->eye + this->target, this->up);
}

glm::mat4 Camera::getProjection() {
	//Projection matrix :
	//45° Field of View, 4:3 ratio, display range : 0.1 unit - 100.0 unit
	return this->projection;
}

glm::vec3 Camera::getPosition() {
	return this->eye;
}


void Camera::setCenter(int width, int height) {
	this->lastX = width / 2.0f;
	this->lastY = height / 2.0f;
}

void Camera::setDeltaTime(float delta) {
	this->deltaTime = delta;
}


void Camera::toFront() {
	this->eye += glm::normalize(this->target) * this->cameraSpeed * this->deltaTime;

	this->notify();
}

void Camera::toBack() {
	this->eye -= glm::normalize(this->target) * this->cameraSpeed * this->deltaTime;

	this->notify();
}

void Camera::toLeft() {
	this->eye -= glm::normalize(glm::cross(this->target, this->up)) * this->cameraSpeed * this->deltaTime;

	this->notify();
}

void Camera::toRight() {
	this->eye += glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed * this->deltaTime;

	this->notify();
}


void Camera::changeDirection(float mouseX, float mouseY) {

	if (this->firstTimeMouse) {
		this->lastX = mouseX;
		this->lastY = mouseY;
		this->firstTimeMouse = false;
	}

	float xOffset = mouseX - this->lastX;
	float yOffset = this->lastY - mouseY;
	this->lastX = mouseX;
	this->lastY = mouseY;

	xOffset *= this->sensitivity;
	yOffset *= this->sensitivity;

	this->yaw += xOffset;
	this->pitch += yOffset;

	if (this->pitch > 89.0f)	this->pitch = 89.0f;
	if (this->pitch < -89.0f)	this->pitch = -89.0f;

	if (this->yaw > 360.0f || this->yaw < -360.0f)
		this->yaw = 0.0f;

	// Direction
	//target.x = cos(fi);
	//target.z = sin(fi);
	//target.y = sin(psi);

	//direction.x = cos(glm::radians(yaw)); 2D rotation, yaw - dolava doprava
	//direction.z = sin(glm::radians(yaw)); direction.y = 0

	glm::vec3 direction;

	direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)); // funguje aj bez * cos(glm::radians(pitch)
	direction.y = sin(glm::radians(this->pitch));
	direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)); // funguje aj bez * cos(glm::radians(pitch)

	this->target = glm::normalize(direction);

	this->notify();
}

void Camera::moveTo(glm::vec3 trans) {
	this->eye = trans;

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
		observer->update(this->getCamera(), this->eye);
}