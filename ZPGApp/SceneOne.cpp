#include "SceneOne.h"

#include "Rectangle.h"

void SceneOne::onLoad() {
	objects->push_back(new Sphere(phongPath));
	objects->push_back(new SuziFlat(phongPath));
	objects->push_back(new SuziSmooth(constantPath));
	objects->push_back(new Plain(blinnPhongPath));

	objects->push_back(new Rectangle(constantPath));


	lights->push_back(new PointLight());

	glm::vec3 vectors[5] = { glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f, 0.0f, -0.5f) };

	int i = 0;
	for (const auto& object : *objects) {
		object->addLight(lights->at(0));

		object->changeColor(glm::vec3(0.0, 1.0, 0.0));
		object->move(vectors[i++]);
	}

	((PointLight*) lights->at(0))->moveTo(glm::vec3(0.0, 0.0, 0.0));
}

void SceneOne::onUpdate() {

	for (const auto& object : *this->objects)
		Renderer::getInstance()->draw(*object);
}
