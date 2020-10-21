#pragma once

#include "Scene.h"
#include "Window.h"

class SceneManager {
public:
	static SceneManager* getInstance();
	
	SceneManager() {}
	~SceneManager() {}

	Scene* loadSceneOne(Window* window);

private:
	static SceneManager* instance;
};

