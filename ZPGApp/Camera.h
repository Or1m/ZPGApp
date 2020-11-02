#pragma once

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp> // glm::to_string()

#include "Subject.h"
#include "Observer.h"
#include "TransformableObject.h"
#include <vector>


class Camera : public Subject, TransformableObject {
public:
	static Camera* getInstance();

	glm::mat4 getCamera();
	glm::mat4 getProjection();
	glm::vec3 getPosition();

	void toFront();
	void toLeft();
	void toBack();
	void toRight();
	void changeDirection(float mouseX, float mouseY);

	void move(glm::vec3 trans);
	void moveTo(glm::vec3 pos);

	void setCenter(int width, int height);
	void setDeltaTime(float delta);

private:
	static Camera* instance;

	glm::mat4 projection;

	glm::vec3 target;
	glm::vec3 up;

	float cameraSpeed;
	float deltaTime;
	float sensitivity;

	float yaw;
	float pitch;
	float lastX;
	float lastY;
	bool firstTimeMouse;

	Camera();
	~Camera() {}
};

