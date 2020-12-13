#pragma once
#include "Object.h"
#include "SkyBox.h"
#include <string>

class ObjectManager {
public:
	static ObjectManager* getInstance();

	ObjectManager()  { }
	~ObjectManager() { }

	Object* loadAndCreateObject(const std::string& modelPath, const std::string& shaderPath, const std::string* texturePath);
	SkyBox* loadAndCreateSkyBox(const std::string& modelPath, const std::string& shaderPath);

	Object* createTerrain(int xCount, int zCount, int width, int height, float range, const std::string& shaderPath);

private:
	static ObjectManager* instance;
};

