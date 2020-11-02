#pragma once

#include "Object.h"
#include "Window.h"

class SceneManager {
public:
	static SceneManager* getInstance();
	
	SceneManager() {}
	~SceneManager() {}

	void loadSceneOne();
	void runSceneOne(Object& object);

	void loadSceneTwo();
	void runSceneTwo(Object& object);

	void loadSceneThree();
	void runSceneThree(std::vector<Object*>& objects, Light& light);

private:
	static SceneManager* instance;
};

