#include "Scene.h"

Scene::Scene() 
:	objects(new std::vector<Object*>()), lights(new std::vector<Light*>()) {}

Scene::~Scene() {
	for (int i = 0; i < this->objects->size(); i++)
		delete this->objects->at(i);

	for (int i = 0; i < this->lights->size(); i++)
		delete this->lights->at(i);

	delete this->objects;
	delete this->lights;
}

void Scene::setSelected(int selected) {
	this->selected = selected;
}
