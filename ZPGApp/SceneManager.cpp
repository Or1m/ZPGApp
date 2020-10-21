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

Scene* SceneManager::loadSceneOne() {
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

	return new Scene(*objects, *lights, test, step, V, vectors);
}
