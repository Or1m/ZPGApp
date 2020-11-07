#include "SceneThree.h"

void SceneThree::onLoad() {
	objects->push_back(new Plain(constantPath));
	objects->push_back(new Sphere(lambertPath));

	lights->push_back(new Light());

	int i = 0;
	glm::vec3 positions[] = { glm::vec3(0.0, -1.0, -.5),  glm::vec3(0.0, 2.0, 0.0) };

	for (const auto& object : *objects) {
		object->addLight(lights->at(0));

		object->useShaderProgram();
		object->init();
		

		object->changeColor(glm::vec3(0.45, 1.0, 1.0));
		object->moveTo(positions[i]);
		i++;
	}

	objects->at(0)->scale(glm::vec3(5.0f, 5.0f, 5.0f));
	//objects->at(1)->scale(glm::vec3(.1f, .1f, .1f));

	lights->at(0)->moveTo(glm::vec3(0.0, 0.0, 0.0));
}

void SceneThree::onUpdate() {

	for (const auto& object : *this->objects) {
		Renderer::getInstance()->draw(*object);

		if (object->getID() == this->selected)
			object->changeColor(glm::vec3(1.0, 0.0, 0.0));

		if (this->selected == objects->at(0)->getID()) {
			//lights->at(0)->moveTo(selectionPos);
			objects->at(1)->moveTo(selectionPos);
		}
	}
}
