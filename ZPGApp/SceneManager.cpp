#include "SceneManager.h"
#include "Object.h"
#include "Light.h"

#include <iostream>
#include <vector>
#include "Renderer.h"
#include "Application.h"
#include "Camera.h"

#include "Sphere.h"
#include "SuziFlat.h"
#include "SuziSmooth.h"
#include "Plain.h"


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

	std::string shaderPath1 = "Resources/Shaders/Phong.shader";
	std::string shaderPath2 = "Resources/Shaders/Constant.shader";
	std::string shaderPath3 = "Resources/Shaders/Lambert.shader";
	std::string shaderPath4 = "Resources/Shaders/Blinn-Phong.shader";

	objects->push_back(new Sphere(shaderPath1));
	objects->push_back(new SuziFlat(shaderPath4));
	objects->push_back(new SuziSmooth(shaderPath3));
	objects->push_back(new Plain(shaderPath2));

	//lights->push_back(new Light());

	glm::vec3 vectors[4] = { glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, -2.0f, 0.0f) };

	Light* light = new Light();

	int i = 0;
	for (const auto& object : *objects) {
		object->addLight(light);

		object->useShaderProgram();
		object->init();

		object->changeColor(glm::vec3(0.0, 1.0, 0.0));
		object->moveTo(vectors[i++]);
	}

	light->moveTo(glm::vec3(0.0, 0.0, 0.0));

	runSceneThree(*objects, *light);
}

void SceneManager::runSceneThree(std::vector<Object*>& objects, Light& light) {

	while(Window::getInstance()->windowShouldNotClose()) {
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