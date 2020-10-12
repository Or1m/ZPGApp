#pragma once
#include "Header.h"

#include "Shader.h"
#include "Object.h"
#include "Window.h"
#include "Renderer.h"

class Application {
public:
	static Application* getInstance();
	static Application* getInstance(int width, int height, const char* title);

	void createObject(std::string& shaderPath, float floats[], int sizeOfPoints, unsigned int indexes[], int countOfIndexes);

	void printVersionInfo();
	void attachCallbacks();
	void testGLM();

	void run();
	
	void setTransform(glm::mat4 M);
	void setTransform(glm::vec3 V);


private:
	static Application* instance;
	Window* window;
	Object* object;
	Renderer* renderer;

	glm::mat4 M;
	glm::vec3 V;

	Application(int width, int height, const char* title);
	~Application();
};