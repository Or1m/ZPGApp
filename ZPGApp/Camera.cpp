#include "Camera.h"

#include <iostream>

#include "Window.h"

Camera* Camera::instance = NULL;

Camera* Camera::getInstance() {
	if (instance == NULL) {
		instance = new Camera();
	}

	return instance;
}

Camera* Camera::getInstance(int width, int height)
{
	if (instance != NULL)
		std::cout << "Warning instance is already created";
	else
		instance = new Camera(width, height);

	return instance;
}

Camera::Camera() : Camera(800, 600) {}

Camera::Camera(int width, int height) 
:	projection(glm::perspective(glm::radians(45.0f), width / (float)height, 0.1f, 100.0f)),
	eye(glm::vec3(0.0f, 0.0f, 3.0f)), target(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
	cameraSpeed(5.0f), deltaTime(0.015f), sensitivity(5.0f),
	yaw(180.0f), pitch(0.0f), lastX(0), lastY(0) {}


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

glm::vec3 Camera::getTarget() {
	return this->target;
}


void Camera::setDeltaTime(float delta) {
	this->deltaTime = delta;
}


void Camera::toFront() {
	this->eye += glm::normalize(this->target) * this->cameraSpeed * this->deltaTime;

	this->notify(*this);
}

void Camera::toBack() {
	this->eye -= glm::normalize(this->target) * this->cameraSpeed * this->deltaTime;

	this->notify(*this);
}

void Camera::toLeft() {
	this->eye -= glm::normalize(glm::cross(this->target, this->up)) * this->cameraSpeed * this->deltaTime;

	this->notify(*this);
}

void Camera::toRight() {
	this->eye += glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed * this->deltaTime;

	this->notify(*this);
}


void Camera::changeDirection(float mouseX, float mouseY) {

	this->lastX = mouseX;
	this->lastY = mouseY;

	
	this->yaw   += this->sensitivity * lastX * this->deltaTime;
	this->pitch += this->sensitivity * lastY * this->deltaTime;


	if (this->pitch > 89.0f)	this->pitch = 89.0f;
	if (this->pitch < -89.0f)	this->pitch = -89.0f;

	if (this->yaw > 360.0f || this->yaw < -360.0f)
		this->yaw = 0.0f;


	glm::vec3 direction;
	direction.x = cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));
	direction.y = sin(glm::radians(this->pitch));
	direction.z = cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));

	this->target = glm::normalize(direction);

	this->notify(*this);
}

void Camera::move(glm::vec3 trans) {
	this->eye += trans;

	this->notify(*this);
}

void Camera::moveTo(glm::vec3 pos) {
	this->eye = pos;

	this->notify(*this);
}