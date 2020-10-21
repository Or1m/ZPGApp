#pragma once

#include "Scene.h"

class SceneManager {
public:
	static SceneManager* getInstance();
	
	SceneManager() {}
	~SceneManager() {}

	Scene* loadSceneOne();

private:
	static SceneManager* instance;
};

