#include "SceneManager.h"
#include "Resources/Models/sphere.h"
#include "Object.h"
#include "Light.h"

#include <iostream>
#include <vector>


SceneManager* SceneManager::instance = NULL;

SceneManager* SceneManager::getInstance() {
	if (instance == NULL) {
		instance = new SceneManager();
	}

	return instance;
}

Scene* SceneManager::loadSceneOne(Window* window) {
	std::vector<Object*> *objects = new std::vector<Object*>();
	std::vector<Light*> *lights = new std::vector<Light*>();

	std::string shaderPath = "Resources/Shaders/Phong.shader";

	objects->push_back(new Object(sphere, sphereCount, NULL, NULL, false, shaderPath));
	lights->push_back(new Light());


	for (const auto& object : *objects) {
		object->useShaderProgram();
		object->init();
	}

	float test = 0.2f;
	float step = 0.003f;
	glm::vec3 V = glm::vec3(0.0, 0.0, 0.0);

	glm::vec3 vectors[4] = { glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, -2.0f, 0.0f) };



	//while (window->windowShouldNotClose()) {
	//	Renderer::getInstance()->clear();

	//	/*if (test > 1)	step = -step;
	//	if (test < 0.2)	step = -step;

	//	V = glm::vec3(0.0, test += step, 0.0);
	//	this->objects[0]->changeColor(V);

	//	for (int i = 0; i < 4; i++) {
	//		this->objects[0]->move(vectors[i]);
	//		Renderer::getInstance()->draw(*this->objects[0]);
	//	}*/

	//	Renderer::getInstance()->draw(*object);

	//	window->pollEvents();
	//	window->swapBuffer();

	//	//Application::getInstance()->countDeltaTime();
	//}

	//window->destroyWindow();
	//window->terminateWindow();
	//exit(EXIT_SUCCESS);

	return new Scene(*objects, *lights, test, step, V, vectors);
}
