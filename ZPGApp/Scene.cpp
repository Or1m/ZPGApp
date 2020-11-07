#include "Scene.h"

Scene::Scene() 
:	objects(new std::vector<Object*>()), lights(new std::vector<Light*>()),
	selected(-1), selectionPos(glm::vec3(0.0)) {}

Scene::~Scene() {
	for (unsigned int i = 0; i < this->objects->size(); i++)
		delete this->objects->at(i);

	for (unsigned int i = 0; i < this->lights->size(); i++)
		delete this->lights->at(i);

	delete this->objects;
	delete this->lights;
}

void Scene::setSelected(int selected, glm::vec3 pos) {
	this->selected = selected;
	this->selectionPos = pos;
}
