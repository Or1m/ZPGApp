#include "Camera.h"

#include <iostream>

Camera* Camera::instance = NULL;

Camera* Camera::getInstance() {
	if (instance == NULL) {
		instance = new Camera();
	}

	return instance;
}

//Projection matrix :
//45� Field of View, 4:3 ratio, display range : 0.1 unit - 100.0 unit
Camera::Camera()
:	projection(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
	eye(glm::vec3(0.0f, 0.0f, 3.0f)), target(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
	cameraSpeed(0.5f), yaw(-90.0f), pitch(0.0f), lastX(400), lastY(300), firstMouse(true) {}


glm::mat4 Camera::getCamera() {
	// eye, eye + target, up
	return glm::lookAt(this->eye, this->eye + this->target, this->up);

	/*return glm::lookAt(	glm::vec3(0.0f, 0.0f, -5.0f),
							glm::vec3(0.0f, 0.0f, 0.0f),
							glm::vec3(0.0f, 1.0f, 0.0f));*/
}

glm::mat4 Camera::getProjection() {
	return this->projection;
}


void Camera::toFront() {
	//glm::vec3 temp = glm::normalize(this->target - this->eye);
	this->eye += this->cameraSpeed * this->target;

	this->notify();
}

void Camera::toBack() {
	//glm::vec3 temp = glm::normalize(this->target - this->eye);
	this->eye -= this->cameraSpeed * this->target;

	this->notify();
}

void Camera::toLeft() {
	//glm::vec3 temp = glm::normalize(glm::cross(this->target - this->eye, this->up));
	this->eye -= glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;;

	this->notify();
}

void Camera::toRight() {
	//glm::vec3 temp = glm::normalize(glm::cross(this->target - this->eye, this->up));
	this->eye += glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;

	this->notify();
}

// pozriet ine varianty
void Camera::changeDirection(int mouseX, int mouseY) {

	if (this->firstMouse)
	{
		this->lastX = mouseX;
		this->lastY = mouseY;
		this->firstMouse = false;
	}

	float xoffset = mouseX - this->lastX;
	float yoffset = this->lastY - mouseY;
	this->lastX = mouseX;
	this->lastY = mouseY;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	this->target = glm::normalize(direction);

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