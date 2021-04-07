#include "SceneMGA.h"
#include "Camera.h"

#include "Utils.h"

void SceneMGA::onLoad() {
	objects->push_back(ObjectFactory::createSkyBox(skyBoxPath, cubeMapPath));
	objects->push_back(ObjectFactory::createGenericObject(enviroPath, constantPath, &enviroTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(setPath, constantPath, &setTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(bookshelfPath, constantPath, &bookshelfTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(livingfPath, constantPath, &livingfTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(barrelPath, constantPath, &barrelTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(stolickyPath, constantPath, &stolickyTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(wellPath, constantPath, &wellTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(platePath, blinnPhongPath, &plateTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(coffeePath, blinnPhongPath, &coffeeTexPath, 2));
	objects->push_back(ObjectFactory::createGenericObject(cofPath, constantPath, &cofTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(grassPath, constantPath, &grassTexPath, 1));
	objects->push_back(ObjectFactory::createGenericObject(studnaPath, phongPath, &studnaTexPath, 3));
	objects->push_back(ObjectFactory::createGenericObject(donutPath, phongPath, &donutTexPath, 4));

	lights->push_back(new DirectionalLight());
	lights->push_back(new PointLight()); // Set
	lights->push_back(new PointLight()); // Well
	lights->push_back(new PointLight()); // Donut

	glm::vec3 positions[] = { 
		glm::vec3(0.0, 0.0, 0.0), 
		glm::vec3(0.0, -1, 0.0),  
		glm::vec3(0.0, -1, 0.0),  
		glm::vec3(0.0, -1, 0.0),
		glm::vec3(0.0, -1, 0.0),
		glm::vec3(0.0, -1, 0.0),
		glm::vec3(0.0, -1, 0.0),
		glm::vec3(0.0, -1, 0.0),
		glm::vec3(0.0, -1, 0.0),
		glm::vec3(0.0, -1, 0.0),
		glm::vec3(0.0, -1, 0.0),
		glm::vec3(0.0, -1, 0.0),
		glm::vec3(0.0, -1, 0.0),
		glm::vec3(0.0, -1, 0.0)
	};
	glm::vec3 scales[] = { 
		glm::vec3(1.0, 1.0, 1.0), 
		glm::vec3(1.0, 1.0, 1.0),		
		glm::vec3(1.0, 1.0, 1.0),  
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0)
	};
	glm::vec3 colors[] = { 
		glm::vec3(1.0, 1.0, 1.0), 
		glm::vec3(1.0, 1.0, 1.0),		
		glm::vec3(1.0, 1.0, 1.0),  
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(1.0, 1.0, 1.0)
	};

	//glm::vec3 scales[] = { glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(20.0f, 20.0f, 20.0f) };

	int i = 0;
	for (const auto& object : *objects) {
		object->addLight(lights->at(0));

		object->move(positions[i]);
		object->scale(scales[i]);

		object->changeColor(colors[i]);
		i++;
	}

	objects->at(9)->addLight(lights->at(1));
	objects->at(12)->addLight(lights->at(1));
	objects->at(12)->addLight(lights->at(2));

	objects->at(13)->addLight(lights->at(1));

	objects->at(13)->addLight(lights->at(1));
	objects->at(13)->addLight(lights->at(2));
	objects->at(13)->addLight(lights->at(3));

	((DirectionalLight*)lights->at(0))->setDirection(glm::vec3(0.5, -1.0, 0.0));
	((PointLight*)(lights->at(1)))->moveTo(glm::vec3(-5.0, 0, 2));
	((PointLight*)(lights->at(2)))->moveTo(glm::vec3(-11.0, -2, 2));
	((PointLight*)(lights->at(3)))->moveTo(glm::vec3(7.0, 0, 2));
}

void SceneMGA::onUpdate() {

	for (const auto& object : *this->objects) {
		Renderer::getInstance()->draw(*object);
	}

	/*if (this->selected == this->objects->at(2)->getID()) {
		this->objects->at(2)->scale(glm::vec3(1.2, 1.2, 1.2));

		this->deselect();
	}*/
}