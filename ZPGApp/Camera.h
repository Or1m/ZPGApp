#pragma once

#include <vector>

#include <glm/vec3.hpp>					
#include <glm/vec4.hpp>					
#include <glm/mat4x4.hpp>				
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>			
#include <glm/gtx/string_cast.hpp>		

#include "Subject.h"
#include "Observer.h"


class Camera : public Subject {
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

	glm::vec3 eye;
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

