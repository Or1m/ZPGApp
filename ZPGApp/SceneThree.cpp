#include "SceneThree.h"

void SceneThree::onLoad() {
	objects->push_back(new Plain(constantPath));

	lights->push_back(new Light());


	for (const auto& object : *objects) {
		object->addLight(lights->at(0));

		object->useShaderProgram();
		object->init();
		object->scale(glm::vec3(15.0f, 15.0f, 15.0f));

		object->changeColor(glm::vec3(0.45, 1.0, 1.0));
		object->moveTo(glm::vec3(0.0, -.5, -.5));
		
	}

	lights->at(0)->moveTo(glm::vec3(0.0, 0.0, 0.0));
}

void SceneThree::onUpdate() {
	for (const auto& object : *this->objects)
		Renderer::getInstance()->draw(*object);
}
