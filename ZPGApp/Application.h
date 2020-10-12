#pragma once
#include "Header.h"

#include "Shader.h"
#include "Object.h"

class Application {
public:
	static Application* getInstance();
	static Application* getInstance(int width, int height, const char* title);

	void createObject(std::string& shaderPath, float floats[], int sizeOfPoints, unsigned int indexes[], int sizeOfIndexes);

	void printVersionInfo();
	void attachCallbacks();
	void testGLM();

	void run();
	
	void setTransform(glm::mat4 M);
	void setTransform(glm::vec3 V);

protected:
	Application(int width, int height, const char* title);
	~Application();

private:
	static Application* instance;
	Shader* shader;
	GLFWwindow* window;
	Object* object;

	glm::mat4 M;
	glm::vec3 V;

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};