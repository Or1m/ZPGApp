#pragma once
#include "Header.h"

#include "Shader.h"
#include "Object.h"

class Application {
public:
	static Application* getInstance();
	static Application* getInstance(WindowOptions* windowOptions, Shaders* shaders, float points[], int sizeOfPoints, unsigned int indices[]);

	void printVersionInfo();
	void attachCallbacks();
	void testGLM();

	void run();
	
	void setShader(const char* vertex_shader, const char* fragment_shader);
	void setPoints(float points[], int sizeOfPoints);
	void setTransform(glm::mat4 M);
	void setTransform(glm::vec3 V);

protected:
	Application();
	Application(WindowOptions* windowOptions, Shaders* shaders, float points[], int sizeOfPoints, unsigned int indices[]);
	~Application();

private:
	static Application* instance;
	Shader* shader;
	GLFWwindow* window;
	Object* object;

	glm::mat4 M;
	glm::vec3 V;

	float* points;
	int sizeOfPoints;
	unsigned int* indices;

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};