#include "SceneFour.h"
#include "Texture.h"

void SceneFour::onLoad() {
	objects->push_back(new Plain(blinnPhongPath, 1));

	lights->push_back(new Light(1));

	for (const auto& object : *objects) {
		object->addLight(lights->at(0));

		object->changeColor(glm::vec3(0.62, 0.49, 1.0));
		object->move(glm::vec3(0.0, -1.0, -.5));
	}

	objects->at(0)->scale(glm::vec3(5.0f, 5.0f, 5.0f));
	lights->at(0)->setDirection(glm::vec3(0.5, -1.0, 0.0));

	Texture texture(texturePath);
	texture.bind();
}

void SceneFour::onUpdate() {
	for (const auto& object : *this->objects) {

		Renderer::getInstance()->draw(*object);
	}
}