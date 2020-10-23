#pragma once

#include "Object.h"
#include "Window.h"

class SceneManager {
public:
	static SceneManager* getInstance();
	
	SceneManager() {}
	~SceneManager() {}

	void loadSceneOne();
	void runSceneOne(std::vector<Object*>* objects);

	void loadSceneTwo();
	void runSceneTwo(Object& object);
private:
	static SceneManager* instance;
};

