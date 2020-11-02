#pragma once

#include "Object.h"
#include "Window.h"
#include "Scene.h"

class SceneManager {
public:
	static SceneManager* getInstance();
	
	SceneManager();
	~SceneManager() {}

	void setScene(Scene& scene);
	void runScene();

private:
	static SceneManager* instance;

	Scene* currentScene;
};

