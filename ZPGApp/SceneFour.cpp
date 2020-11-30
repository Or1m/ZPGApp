#include "SceneFour.h"
#include "Texture.h"

void SceneFour::onLoad() {
	objects->push_back(new TexturedPlain(constantPath, 1));

	lights->push_back(new Light(1));

	Texture* texture = new Texture(texturePath);

	for (const auto& object : *objects) {
		object->sendUniformToShader("myTexture", 0);
		object->sendUniformToShader("hasTexture", 1);

		object->addLight(lights->at(0));

		object->changeColor(glm::vec3(1.0, 1.0, 1.0));
		object->move(glm::vec3(0.0, -1.0, -.5));
	}

	objects->at(0)->scale(glm::vec3(20.0f, 20.0f, 20.0f));
	lights->at(0)->setDirection(glm::vec3(0.5, -1.0, 0.0));
}

void SceneFour::onUpdate() {
	for (const auto& object : *this->objects) {

		Renderer::getInstance()->draw(*object);
	}
}