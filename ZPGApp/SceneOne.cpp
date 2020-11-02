#include "SceneOne.h"

void SceneOne::onLoad() {
	objects->push_back(new Sphere(phongPath));
	objects->push_back(new SuziFlat(blinnPhongPath));
	objects->push_back(new SuziSmooth(lambertPath));
	objects->push_back(new Plain(constantPath));

	lights->push_back(new Light());

	glm::vec3 vectors[4] = { glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, -2.0f, 0.0f) };

	int i = 0;
	for (const auto& object : *objects) {
		object->addLight(lights->at(0));

		object->useShaderProgram();
		object->init();

		object->changeColor(glm::vec3(0.0, 1.0, 0.0));
		object->moveTo(vectors[i++]);
	}

	lights->at(0)->moveTo(glm::vec3(0.0, 0.0, 0.0));
}

void SceneOne::onUpdate() {

	for (const auto& object : *this->objects)
		Renderer::getInstance()->draw(*object);
}
