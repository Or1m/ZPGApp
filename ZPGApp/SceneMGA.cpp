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

	lights->push_back(new DirectionalLight());

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

	((DirectionalLight*)lights->at(0))->setDirection(glm::vec3(0.5, -1.0, 0.0));
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