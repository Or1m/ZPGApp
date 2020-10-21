#include "Scene.h"
#include "Renderer.h"
#include "Application.h"
#include "Resources/Models/sphere.h"

Scene::Scene(std::vector<Object*>& objects, std::vector<Light*>& lights, float test, float step, glm::vec3 V, glm::vec3 vectors[]) 
:	objects(objects), lights(lights), test(test), step(step), V(V), vectors(vectors) {}

void Scene::runScene(Window* window) {
	std::string shaderPath = "Resources/Shaders/Phong.shader";

	Object* object = new Object(sphere, sphereCount, NULL, NULL, false, shaderPath);

	object->useShaderProgram();
	object->init();

	object->changeColor(V);

	while (window->windowShouldNotClose()) {
		Renderer::getInstance()->clear();

		/*if (test > 1)	step = -step;
		if (test < 0.2)	step = -step;

		V = glm::vec3(0.0, test += step, 0.0);
		this->objects[0]->changeColor(V);

		for (int i = 0; i < 4; i++) {
			this->objects[0]->move(vectors[i]);
			Renderer::getInstance()->draw(*this->objects[0]);
		}*/

		Renderer::getInstance()->draw(*object);

		window->pollEvents();
		window->swapBuffer();

		//Application::getInstance()->countDeltaTime();
	}

	window->destroyWindow();
	window->terminateWindow();
	exit(EXIT_SUCCESS);
}