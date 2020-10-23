#include "SceneManager.h"
#include "Resources/Models/sphere.h"
#include "Object.h"
#include "Light.h"

#include <iostream>
#include <vector>
#include "Renderer.h"
#include "Application.h"
#include "Camera.h"


SceneManager* SceneManager::instance = NULL;

SceneManager* SceneManager::getInstance() {
	if (instance == NULL) {
		instance = new SceneManager();
	}

	return instance;
}


void SceneManager::loadSceneOne() {

	std::string shaderPath = "Resources/Shaders/Phong.shader";

	Object* object = new Object(sphere, sphereCount, NULL, NULL, false, shaderPath);

	object->useShaderProgram();
	object->init();

	runSceneOne(*object);
}

void SceneManager::runSceneOne(Object& object) {
	float test = 0.2f;
	float step = 0.003f;
	glm::vec3 V = glm::vec3(1.0, 1.0, 1.0);

	glm::vec3 vectors[4] = { glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, -2.0f, 0.0f) };

	while (Window::getInstance()->windowShouldNotClose()) {
		Renderer::getInstance()->clear();

		if (test > 1)	step = -step;
		if (test < 0.2)	step = -step;

		V = glm::vec3(0.0, test += step, 0.0);
		object.changeColor(V);

		for (int i = 0; i < 4; i++) {
			object.moveTo(vectors[i]);
			Renderer::getInstance()->draw(object);
		}

		Window::getInstance()->pollEvents();
		Window::getInstance()->swapBuffer();

		Application::getInstance()->countDeltaTime();
	}

	Window::getInstance()->destroyWindow();
	Window::getInstance()->terminateWindow();
	exit(EXIT_SUCCESS);
}


void SceneManager::loadSceneTwo() {

	std::string shaderPath = "Resources/Shaders/Phong.shader";

	Object* object = new Object(sphere, sphereCount, NULL, NULL, false, shaderPath);

	object->useShaderProgram();
	object->init();

	runSceneTwo(*object);
}

void SceneManager::runSceneTwo(Object& object) {
	object.changeColor(glm::vec3(0.0, 0.0, 1.0));
	object.moveTo(glm::vec3(0.0, 0.0, 2.0));

	Camera::getInstance()->moveTo(glm::vec3(0.0, 0.0, 5.0));

	while (Window::getInstance()->windowShouldNotClose()) {
		Renderer::getInstance()->clear();

		Renderer::getInstance()->draw(object);

		Window::getInstance()->pollEvents();
		Window::getInstance()->swapBuffer();

		Application::getInstance()->countDeltaTime();
	}

	Window::getInstance()->destroyWindow();
	Window::getInstance()->terminateWindow();
	exit(EXIT_SUCCESS);
}


void SceneManager::loadSceneThree() {

	std::vector<Object*>* objects = new std::vector<Object*>();
	//std::vector<Light*>* lights = new std::vector<Light*>();

	std::string shaderPath = "Resources/Shaders/Phong.shader";

	objects->push_back(new Object(sphere, sphereCount, NULL, NULL, false, shaderPath));
	objects->push_back(new Object(sphere, sphereCount, NULL, NULL, false, shaderPath));
	objects->push_back(new Object(sphere, sphereCount, NULL, NULL, false, shaderPath));
	objects->push_back(new Object(sphere, sphereCount, NULL, NULL, false, shaderPath));
	//lights->push_back(new Light());

	glm::vec3 vectors[4] = { glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, -2.0f, 0.0f) };

	int i = 0;
	for (const auto& object : *objects) {
		object->useShaderProgram();
		object->init();

		object->changeColor(glm::vec3(0.0, 0.0, 1.0));
		object->moveTo(vectors[i++]);
	}

	runSceneThree(*objects);
}

void SceneManager::runSceneThree(std::vector<Object*>& objects) {
		
	while (Window::getInstance()->windowShouldNotClose()) {
		Renderer::getInstance()->clear();

		for (const auto& object : objects)
			Renderer::getInstance()->draw(*object);

		Window::getInstance()->pollEvents();
		Window::getInstance()->swapBuffer();

		Application::getInstance()->countDeltaTime();
	}

	Window::getInstance()->destroyWindow();
	Window::getInstance()->terminateWindow();
	exit(EXIT_SUCCESS);
}