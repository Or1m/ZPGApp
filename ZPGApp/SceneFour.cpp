#include "SceneFour.h"

void SceneFour::onLoad() {
	objects->push_back(ObjectManager::getInstance()->loadAndCreateSkyBox(skyBoxPath, cubeMapPath));
	objects->push_back(ObjectManager::getInstance()->createTerrain(64, 64, 50, 50, 1, lambertPath));

	//objects->push_back(new TexturedPlain(constantPath, &groundTexturePath, 1));
	//objects->push_back(ObjectManager::getInstance()->loadAndCreateObject(domePath, constantPath, &skyTexturePath));
	
	lights->push_back(new DirectionalLight());

	glm::vec3 positions[] = { glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, -1.0, -.5),  glm::vec3(0.0, -3.0, 0.0) };
	glm::vec3 scales[]    = { glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0),   glm::vec3(1.0, 1.0, 1.0)  };
	glm::vec3 colors[]	  = { glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 1.0, 0.0),   glm::vec3(1.0, 1.0, 1.0)  };

	//glm::vec3 scales[] = { glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(20.0f, 20.0f, 20.0f) };

	int i = 0;
	for (const auto& object : *objects) {
		object->addLight(lights->at(0));

		object->move(positions[i]);
		object->scale(scales[i]);

		object->changeColor(colors[i]);
		i++;
	}

	((DirectionalLight*) lights->at(0))->setDirection(glm::vec3(0.5, -1.0, 0.0));
}

void SceneFour::onUpdate() {

	for (const auto& object : *this->objects) {
		Renderer::getInstance()->draw(*object);
	}
}