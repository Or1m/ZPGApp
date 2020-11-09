#pragma once

#include "Scene.h"

class SceneManager {
public:
	static SceneManager* getInstance();
	
	SceneManager();
	~SceneManager();

	void setScene(Scene& scene);
	Scene* getScene();

	void runScene();

private:
	static SceneManager* instance;

	Scene* currentScene;
};