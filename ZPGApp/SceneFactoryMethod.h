#pragma once

#include "Scene.h"

class SceneFactoryMethod {
public:
	SceneFactoryMethod() {}
	~SceneFactoryMethod() {}

	static Scene* makeScene(int choice);
};