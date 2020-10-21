#pragma once
#include <vector>
#include "Object.h"
#include "Light.h"
#include "Window.h"

class Scene {
public:
	Scene(std::vector<Object*>& objects, std::vector<Light*>& lights, float test, float step, glm::vec3 V, glm::vec3 vectors[]);
	void runScene(Window* window);

private:
	std::vector<Object*> objects;
	std::vector<Light*> lights;
	float test;
	float step;
	glm::vec3 V;
	glm::vec3 *vectors;
};

