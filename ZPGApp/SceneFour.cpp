#include "SceneFour.h"
#include "Camera.h"

#include "Utils.h"

void SceneFour::onLoad() {
	objects->push_back(ObjectFactory::createSkyBox(skyBoxPath, cubeMapPath));
	objects->push_back(ObjectFactory::createTerrain(32, 32, 100, 100, 3, terraintPath));

	//objects->push_back(new TexturedPlain(constantPath, &groundTexturePath));
	//objects->push_back(ObjectManager::loadAndCreateObject(domePath, constantPath, &skyTexturePath));
	objects->push_back(new SuziFlat(lambertPath, 1));
	
	lights->push_back(new DirectionalLight());

	glm::vec3 positions[] = { glm::vec3(0.0, 0.0, 0.0), glm::vec3(-50.0, -1.0, -50.0),  glm::vec3(0.0, 1.0, 0.0)  };
	glm::vec3 scales[]    = { glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0),		glm::vec3(1.0, 1.0, 1.0)  };
	glm::vec3 colors[]	  = { glm::vec3(1.0, 1.0, 1.0), fromRGB(56, 44, 11),			glm::vec3(1.0, 0.0, 1.0)  };

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

	this->arr = new glm::vec3[] {
		glm::vec3(0.0, 1.0, 0.0),
		glm::vec3(2.0, 4.0, 2.0),
		glm::vec3(0.0, 4.0, 3.0),
		glm::vec3(8.0, 1.0, 0.0),
	};
}

void SceneFour::onUpdate() {

	if (t > 1 || t < 0)
		step = -step;

	t += step;

	objects->at(2)->moveTo(calcBazier(t, arr));

	for (const auto& object : *this->objects) {
		Renderer::getInstance()->draw(*object);
	}
}