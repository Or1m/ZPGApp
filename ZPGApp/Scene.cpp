#include "Scene.h"

Scene::Scene() 
:	objects(new std::vector<Object*>()), lights(new std::vector<Light*>()) {}
