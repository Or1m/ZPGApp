#include "SceneThree.h"
#include "Camera.h"

void SceneThree::onLoad() {
	objects->push_back(new Plain(blinnPhongPath));
	objects->push_back(new SuziFlat(lambertPath));

	// Preco len v tomto poradi?
	lights->push_back(new Light(2));
	lights->push_back(new Light());

	glm::vec3 positions[] = { glm::vec3(0.0, -1.0, -.5),  glm::vec3(0.0, 2.0, -3.0) };
	glm::vec3 test = fromRGB(192, 242, 67);
	glm::vec3 colors[] = { glm::vec3(0.62, 0.49, 1.0), test };

	int i = 0;
	for (const auto& object : *objects) {
		object->addLight(lights->at(0));
		object->addLight(lights->at(1));

		object->changeColor(colors[i]);
		object->move(positions[i]);
		i++;
	}

	objects->at(0)->scale(glm::vec3(5.0f, 5.0f, 5.0f));

	lights->at(1)->moveTo(glm::vec3(0.0, 0.0, 0.0));

	lights->at(0)->moveTo(glm::vec3(0.0, 6.0, -3.0));
	lights->at(0)->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
}

void SceneThree::onUpdate() {
	
	for (const auto& object : *this->objects) {
		lights->at(0)->moveTo(Camera::getInstance()->getPosition());
		lights->at(0)->setDirection(Camera::getInstance()->getTarget());

		Renderer::getInstance()->draw(*object);

		if (this->selected == object->getID() && object->getID() > 2) {
			object->changeColor(glm::vec3(1.0, 0.0, 0.0));
			this->deselect();
		}
	}

	if (this->selected == this->objects->at(0)->getID()) {
		//lights->at(0)->moveTo(selectionPos);
		//objects->at(1)->moveTo(selectionPos);

		Sphere* sphere = new Sphere(blinnPhongPath);
		sphere->changeColor(fromRGB(133, 255, 139));
		sphere->addLight(lights->at(0));

		lights->at(0)->moveTo(glm::vec3(0.0, 0.0, 0.0));
		sphere->move(selectionPos);

		objects->push_back(sphere);
		this->deselect();
	}

	else if (this->selected == this->objects->at(1)->getID()) {
		this->objects->at(1)->scale(glm::vec3(1.2, 1.2, 1.2));
		this->deselect();
	}
}
