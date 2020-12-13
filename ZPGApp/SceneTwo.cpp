#include "SceneTwo.h"
#include "Camera.h"

SceneTwo::SceneTwo() 
:	vectors(new glm::vec3[4]{ glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(-2.0f, 2.0f, 0.0f), glm::vec3(0.0f, -4.0f, 0.0f), glm::vec3(-2.0f, 2.0f, 0.0f) }) {}

SceneTwo::~SceneTwo() {
	delete[] this->vectors;
}


void SceneTwo::onLoad() {

	objects->push_back(new Object(sphere, sphereCount, NULL, NULL, false, phongPath, false, 3));

	lights->push_back(new PointLight());
	lights->push_back(new DirectionalLight());
	lights->push_back(new SpotLight());

	// Bacha pocet svetiel sa berie z indexu, nezakomentovavat mimo poradia
	for (const auto& object : *objects) {
		object->addLight(lights->at(0));
		object->addLight(lights->at(1));
		object->addLight(lights->at(2));

		object->changeColor(glm::vec3(0.0, 0.0, 1.0));
		object->move(glm::vec3(-2.0f, 0.0f, 0.0f));
	}

	((PointLight*) lights->at(0))->moveTo(glm::vec3(4.0, 0.0, 0.0));
	((DirectionalLight*) lights->at(1))->setDirection(glm::vec3(0.5, -1.0, 0.0));
}

void SceneTwo::onUpdate() {

	for (int i = 0; i < 4; i++) {
		objects->at(0)->move(vectors[i]);

		((SpotLight*) lights->at(2))->moveTo(Camera::getInstance()->getPosition());
		((SpotLight*)lights->at(2))->setDirection(Camera::getInstance()->getTarget());


		Renderer::getInstance()->draw(*objects->at(0));
	}
}
