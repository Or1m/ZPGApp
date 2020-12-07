#include "ObjectManager.h"

#include <iostream>
#include "Vendor/objloader.h"


ObjectManager* ObjectManager::instance = NULL;

ObjectManager* ObjectManager::getInstance() {
	if (instance == NULL) {
		instance = new ObjectManager();
	}

	return instance;
}

Object* ObjectManager::loadAndCreateObject(const std::string& modelPath, const std::string& shaderPath, const std::string& texturePath)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	loadOBJ(modelPath.c_str(), vertices, uvs, normals);

	int count = vertices.size();
	int size = count * 8;

	float* arr = new float[size];

	for (int i = 0, j = 0; i < size; i += 8, j += 1) {
		arr[i + 0] = vertices[j].x;
		arr[i + 1] = vertices[j].y;
		arr[i + 2] = vertices[j].z;

		arr[i + 3] = normals[j].x;
		arr[i + 4] = normals[j].y;
		arr[i + 5] = normals[j].z;

		arr[i + 6] = uvs[j].x;
		arr[i + 7] = uvs[j].y;
	}

	return new Object(arr, count, NULL, NULL, false, shaderPath, texturePath);
}
