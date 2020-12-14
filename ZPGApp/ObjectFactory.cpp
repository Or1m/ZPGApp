#include "ObjectFactory.h"
#include "Vendor/objloader.h"

#include "glm/gtc/noise.hpp"

#include <iostream>

SkyBox* ObjectFactory::createSkyBox(const std::string& modelPath, const std::string& shaderPath) {

	int count;
	float* arr = internalLoadObject(modelPath, count);

	return new SkyBox(arr, count, NULL, NULL, false, shaderPath);
}

Terrain* ObjectFactory::createTerrain(int xCount, int zCount, int width, int height, float range, const std::string& shaderPath) {
	
	std::vector<glm::vec3> plain;
	float densityX = width / (float)xCount;
	float densityZ = height / (float)zCount;

	for (float i = 0; i < (float)width; i += densityX) {
		for (float j = 0; j < (float)height; j += densityZ) {
			glm::vec3 point = glm::vec3(i, 0, j);
			plain.push_back(point);
		}
	}

	std::vector<glm::vec3> pos, norms;
	int plainSize = plain.size();

	for (int i = 0; i < plainSize; i++) {
		glm::vec3 v1 = plain.at(i);
		glm::vec3 v2 = glm::vec3(plain.at(i).x + densityX, plain.at(i).y, plain.at(i).z);
		glm::vec3 v3 = glm::vec3(plain.at(i).x, plain.at(i).y, plain.at(i).z + densityZ);
		glm::vec3 v4 = glm::vec3(plain.at(i).x + densityX, plain.at(i).y, plain.at(i).z + densityZ);

		if (v1.x != width - densityX && v1.z != height - densityZ) {
			pos.push_back(v1);
			pos.push_back(v2);
			pos.push_back(v3);
			pos.push_back(v4);
			pos.push_back(v3);
			pos.push_back(v2);
		}
	}

	processPerlin(pos, norms, range);
	float* arr = convertToArr(pos, norms);

	return new Terrain(arr, pos.size(), NULL, NULL, false, shaderPath);
}

Doll* ObjectFactory::createDoll(const std::string& modelPath, const std::string& shaderPath, const std::string* texturePath, int lightCount) {
	int count;
	float* arr = internalLoadObject(modelPath, count);

	return new Doll(arr, count, shaderPath, texturePath, lightCount);
}


void ObjectFactory::processPerlin(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& norms, float range) {
	int posSize = pos.size();

	for (int i = 0; i < posSize; i++) {
		glm::vec2 v = glm::vec2(pos.at(i).x, pos.at(i).z);
		float newY = range * glm::perlin(v);

		pos.at(i) = glm::vec3(pos.at(i).x, newY, pos.at(i).z);
	}

	for (int i = 0; i < posSize; i += 3) {
		glm::vec3 vector1 = pos.at(i + 1) - pos.at(i);
		glm::vec3 vector2 = pos.at(i + 2) - pos.at(i);
		glm::vec3 new_normal = glm::cross(vector1, vector2);

		norms.push_back(-1.0f * new_normal);
		norms.push_back(-1.0f * new_normal);
		norms.push_back(-1.0f * new_normal);
	}
}

float* ObjectFactory::convertToArr(const std::vector<glm::vec3>& pos, const std::vector<glm::vec3>& norms) {
	int size = pos.size() * 6;
	float* arr = new float[size];

	for (int i = 0, j = 0; i < size; i += 6, j += 1) {
		arr[i + 0] = pos[j].x;
		arr[i + 1] = pos[j].y;
		arr[i + 2] = pos[j].z;

		arr[i + 3] = norms[j].x;
		arr[i + 4] = norms[j].y;
		arr[i + 5] = norms[j].z;
	}

	return arr;
}


float* ObjectFactory::internalLoadObject(const std::string& modelPath, int& count) {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	loadOBJ(modelPath.c_str(), vertices, uvs, normals);

	count = vertices.size();
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

	return arr;
}