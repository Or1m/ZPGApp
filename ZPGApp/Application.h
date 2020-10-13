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

	void createObject(std::string& shaderPath, float floats[], int sizeOfPoints, unsigned int indexes[], int countOfIndexes, bool isWithIndexes);

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

	void initShaderProgram();
	Application(int width, int height, const char* title);
	~Application();
};