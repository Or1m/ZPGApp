#include "SceneTwo.h"

SceneTwo::SceneTwo() 
:	vectors(new glm::vec3[4]{ glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, -2.0f, 0.0f) }) {}

SceneTwo::~SceneTwo() {
	delete[] this->vectors;
}


void SceneTwo::onLoad() {

	objects->push_back(new Object(sphere, sphereCount, NULL, NULL, false, lambertPath));
	lights->push_back(new Light());

	for (const auto& object : *objects) {
		object->addLight(lights->at(0));

		object->useShaderProgram();
		object->init();
		object->changeColor(glm::vec3(0.0, 0.0, 1.0));
	}

	lights->at(0)->moveTo(glm::vec3(0.0, 0.0, 0.0));
}

void SceneTwo::onUpdate() {

	for (int i = 0; i < 4; i++) {
		objects->at(0)->moveTo(vectors[i]);
		Renderer::getInstance()->draw(*objects->at(0));
	}
}
