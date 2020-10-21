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

	object->changeColor(glm::vec3(1.0, 1.0, 0.0));

	glm::vec3 vectors[4] = { glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, -2.0f, 0.0f) };

	while (window->windowShouldNotClose()) {
		Renderer::getInstance()->clear();

		if (test > 1)	step = -step;
		if (test < 0.2)	step = -step;

		V = glm::vec3(0.0, test += step, 0.0);
		object->changeColor(V);

		for (int i = 0; i < 4; i++) {
			object->move(vectors[i]);
			Renderer::getInstance()->draw(*object);
		}

		//Renderer::getInstance()->draw(*object);

		window->pollEvents();
		window->swapBuffer();

		Application::getInstance()->countDeltaTime();
	}

	window->destroyWindow();
	window->terminateWindow();
	exit(EXIT_SUCCESS);
}