#include "Application.h"
#include "Camera.h"
#include "SceneManager.h"

Application* Application::instance = NULL;

Application* Application::getInstance() {

	if (instance == NULL) {
		instance = new Application(800, 600, "ZPG");
	}

	return instance;
}

Application* Application::getInstance(int width, int height, const char* title) {

	if (instance != NULL)
		std::cout << "Warning instance is already created";
	else
		instance = new Application(width, height, title);

	return instance;
}

Application::Application(int width, int height, const char* title)
:	window(Window::getInstance(width, height, title)), deltaTime(0.0), lastFrame(0.0) {}


void Application::run(int scene) {
	
	switch (scene)
	{
	case 1:
		SceneManager::getInstance()->loadSceneOne();
	case 2:
		SceneManager::getInstance()->loadSceneTwo();
	case 3:
		SceneManager::getInstance()->loadSceneThree();
	default:
		break;
	}
}

void Application::countDeltaTime() {
	float currentFrame = (float)glfwGetTime();
	this->deltaTime = currentFrame - this->lastFrame;
	this->lastFrame = currentFrame;

	Camera::getInstance()->setDeltaTime(this->deltaTime);
}

void Application::printVersionInfo() const {

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Application::attachCallbacks() const {
	this->window->attachCallbacks();
}