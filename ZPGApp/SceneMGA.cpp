#include "SceneMGA.h"
#include "Camera.h"

#include "Utils.h"

static int counter = 0;

void SceneMGA::onLoad() {
	objects->push_back(ObjectFactory::createSkyBox(skyBoxPath, cubeMapPath)); // 0
	objects->push_back(ObjectFactory::createGenericObject(enviroPath, constantPath, &enviroTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(setPath, constantPath, &setTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(bookshelfPath, constantPath, &bookshelfTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(livingfPath, constantPath, &livingfTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(barrelPath, constantPath, &barrelTexPath, 1)); // 5
	objects->push_back(ObjectFactory::createGenericObject(stolickyPath, constantPath, &stolickyTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(wellPath, constantPath, &wellTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(platePath, blinnPhongPath, &plateTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(coffeePath, blinnPhongPath, &coffeeTexPath, 2));
	objects->push_back(ObjectFactory::createGenericObject(cofPath, constantPath, &cofTexPath, 1)); // 10
	objects->push_back(ObjectFactory::createGenericObject(grassPath, constantPath, &grassTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(studnaPath, phongPath, &studnaTexPath, 3));
	objects->push_back(ObjectFactory::createGenericObject(donutPath, phongPath, &donutTexPath, 3)); // 13
	objects->push_back(ObjectFactory::createGenericObject(bigDonutPath, phongPath, &donutTexPath, 4)); // 14

	lights->push_back(new DirectionalLight());
	lights->push_back(new PointLight()); // Set
	lights->push_back(new PointLight()); // Well
	lights->push_back(new PointLight()); // Donut

	glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 scaleAndColor = glm::vec3(1.0, 1.0, 1.0);

	this->arr = new glm::vec3[] {
		glm::vec3(-5.52, -0.824, -0.33), // well 1
		glm::vec3(-6.22, -0.264, -0.18), // well rope
		glm::vec3(-6.847, 0.457, 0.54), // well under roof
		glm::vec3(-5.242, 0.879, -0.977), // well roof
		glm::vec3(0.548, -1.305, -0.99), // chair
		glm::vec3(5.74, -1.058, -0.6), // books living - zniz
		glm::vec3(8.025, -1.5496, -2.075), // bookshelf
		glm::vec3(7.386, -0.898, 1.409) // barrel
	};

	int i = 0;
	for (const auto& object : *objects) {
		object->addLight(lights->at(0));

		if (i == 1) {
			pos = glm::vec3(0.0, -1.0, 0.0);
		}

		object->move(pos);
		object->scale(scaleAndColor);
		object->changeColor(scaleAndColor);

		i++;
	}

	objects->at(14)->moveTo(glm::vec3(-9.0, -100.24, 5.75));

	objects->at(9)->addLight(lights->at(1));

	objects->at(12)->addLight(lights->at(1));
	objects->at(12)->addLight(lights->at(2));

	objects->at(13)->addLight(lights->at(1));
	objects->at(13)->addLight(lights->at(2));

	objects->at(14)->addLight(lights->at(1));
	objects->at(14)->addLight(lights->at(2));
	objects->at(14)->addLight(lights->at(3));

	((DirectionalLight*)lights->at(0))->setDirection(glm::vec3(0.5, -1.0, 0.0));
	((PointLight*)(lights->at(1)))->moveTo(glm::vec3(-5.0, 0, 2));
	((PointLight*)(lights->at(2)))->moveTo(glm::vec3(-11.0, -2, 2));
	((PointLight*)(lights->at(3)))->moveTo(glm::vec3(-9.0, 0.5, 5.75));
}

void SceneMGA::onUpdate() {

	for (const auto& object : *this->objects) {
		Renderer::getInstance()->draw(*object);
	}

	if (this->selected == this->objects->at(13)->getID()) {
		if (counter < MAX) {
			this->objects->at(13)->moveTo(arr[randomWithoutRepetition()]);
			counter++;
		}
		else
		{
			this->objects->at(13)->moveTo(glm::vec3(0.0, -1.0, 0.0));
			this->objects->at(14)->moveTo(glm::vec3(-9.0, -0.24, 5.75));
			
			clearVisited();
			counter = 0;
		}

		this->deselect();
	}
}