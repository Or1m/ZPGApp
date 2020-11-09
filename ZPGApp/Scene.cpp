#include "Scene.h"

#include "SceneOne.h"
#include "SceneTwo.h"
#include "SceneThree.h"

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

void Scene::deselect() {
	this->selected = -1;
}


// Factory method
Scene* Scene::makeScene(int choice)
{
	switch (choice)
	{
	case 1:
		return new SceneOne();
		break;
	case 2:
		return new SceneTwo();
		break;
	case 3:
		return new SceneThree();
		break;
	default:
		return nullptr;
	}
}