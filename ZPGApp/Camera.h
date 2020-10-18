#pragma once

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp> // glm::to_string()

#include "ISubject.h"
#include "IObserver.h"
#include <vector>

class Camera : public ISubject {
public:
	static Camera* getInstance();

	glm::mat4 getCamera();
	glm::mat4 getProjection();

	void toFront();
	void toLeft();
	void toBack();
	void toRight();
	void changeDirection(int mouseX, int mouseY);

	void attach(IObserver* observer) override;
	void detach(IObserver* observer) override;

private:
	static Camera* instance;

	glm::mat4 projection;

	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;

	float cameraSpeed;
	float yaw;
	float pitch;
	float lastX;
	float lastY;
	bool firstMouse;

	std::vector<IObserver*> observers;

	void notify() override;
	
	Camera();
	~Camera() {}
};

