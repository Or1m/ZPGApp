#include "SceneThree.h"

void SceneThree::onLoad() {
	objects->push_back(new Plain(blinnPhongPath));
	objects->push_back(new SuziFlat(lambertPath));

	lights->push_back(new Light());


	glm::vec3 positions[] = { glm::vec3(0.0, -1.0, -.5),  glm::vec3(0.0, 2.0, -5.0) };
	glm::vec3 test = fromRGB(192, 242, 67);
	glm::vec3 colors[] = { glm::vec3(0.62, 0.49, 1.0), test };

	int i = 0;
	for (const auto& object : *objects) {
		object->addLight(lights->at(0));

		object->changeColor(colors[i]);
		object->moveTo(positions[i]);
		i++;
	}

	objects->at(0)->scale(glm::vec3(5.0f, 5.0f, 5.0f));
	lights->at(0)->moveTo(glm::vec3(0.0, 0.0, 0.0));
}

void SceneThree::onUpdate() {
	
	for (const auto& object : *this->objects) {
		Renderer::getInstance()->draw(*object);

		if (this->selected == object->getID() && object->getID() > 1) {
			object->changeColor(glm::vec3(1.0, 0.0, 0.0));
			this->selected = -1;
		}
	}

	if (this->selected == objects->at(0)->getID()) {
		//lights->at(0)->moveTo(selectionPos);
		//objects->at(1)->moveTo(selectionPos);

		Sphere* sphere = new Sphere(lambertPath);
		sphere->changeColor(fromRGB(133, 255, 139));
		sphere->addLight(lights->at(0));

		lights->at(0)->moveTo(glm::vec3(0.0, 0.0, 0.0));
		sphere->moveTo(selectionPos);

		objects->push_back(sphere);
		this->selected = -1;
	}
}
