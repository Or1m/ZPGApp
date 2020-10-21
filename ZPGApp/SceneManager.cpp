#include "SceneManager.h"
#include "Resources/Models/sphere.h"
#include "Object.h"

#include <iostream>
#include <vector>


SceneManager* SceneManager::instance = NULL;

SceneManager* SceneManager::getInstance() {
	if (instance == NULL) {
		instance = new SceneManager();
	}

	return instance;
}

void SceneManager::loadSceneOne() {
	std::vector<Object*> objects;

	std::string shaderPath = "Resources/Shaders/Phong.shader";

	objects.push_back(new Object(sphere, sphereCount, NULL, NULL, false, shaderPath));
}
