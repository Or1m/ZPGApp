#pragma once
//#include "Header.h"

// Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp> // glm::to_string()

#include "Object.h"
#include "Window.h"
#include "Renderer.h"

class Application {
public:
	static Application* getInstance();
	static Application* getInstance(int width, int height, const char* title);

	void createObject(std::string& shaderPath, const float floats[], const int sizeOfPoints, unsigned int indexes[], int countOfIndexes, bool isWithIndexes);

	void printVersionInfo() const;
	void attachCallbacks() const;

	void run(int scene);

private:
	static Application* instance;
	Window* window;
	Object* object;
	Renderer* renderer;

	float deltaTime;
	float lastFrame;

	void initShaderProgram() const;
	void initObject() const;
	void countDeltaTime();

	Application(int width, int height, const char* title);
	~Application();
};