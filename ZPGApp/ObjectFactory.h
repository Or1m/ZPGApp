#pragma once

#include <string>

#include "Object.h"

#include "SkyBox.h"
#include "Terrain.h"
#include "Sphere.h"
#include "SuziFlat.h"
#include "SuziSmooth.h"
#include "Plain.h"
#include "TexturedPlain.h"
#include "Doll.h"

class ObjectFactory {
public:
	static SkyBox* createSkyBox(const std::string& modelPath, const std::string& shaderPath);
	static Terrain* createTerrain(int xCount, int zCount, int width, int height, float range, const std::string& shaderPath);
	static Doll* createDoll(const std::string& modelPath, const std::string& shaderPath, const std::string* texturePath, int lightCount);

private:
	static float* internalLoadObject(const std::string& modelPath, int& count);
	static void processPerlin(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& norms, float range);
	static float* convertToArr(const std::vector<glm::vec3>& pos, const std::vector<glm::vec3>& norms);
};