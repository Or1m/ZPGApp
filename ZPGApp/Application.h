#pragma once

#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>			// glm::value_ptr
#include <glm/gtx/string_cast.hpp>		// glm::to_string()

#include "Window.h"

class Application {
public:
	static Application* getInstance();
	static Application* getInstance(int width, int height, const char* title);

	void printVersionInfo() const;
	void attachCallbacks() const;

	float countDeltaTime();

	void run(int scene);

private:
	static Application* instance;
	Window* window;

	float deltaTime;
	float lastFrame;
	
	Application(int width, int height, const char* title);
	~Application() {}
};