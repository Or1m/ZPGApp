#pragma once
#include "Object.h"
#include <string>

class ObjectManager {
public:
	static ObjectManager* getInstance();

	ObjectManager()  { }
	~ObjectManager() { }

	Object* loadAndCreateObject(const std::string& modelPath, const std::string& shaderPath, const std::string& texturePath);


private:
	static ObjectManager* instance;
};

