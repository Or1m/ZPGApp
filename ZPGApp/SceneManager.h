#pragma once
class SceneManager {
public:
	static SceneManager* getInstance();
	
	SceneManager() {}
	~SceneManager() {}

	void loadSceneOne();

private:
	static SceneManager* instance;
};

