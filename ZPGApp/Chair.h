#pragma once

#include "Object.h"

class Chair : public Object {
public:
	Chair(const float points[], const int countOfPoints, const std::string& shaderPath, const std::string* texturePath, int lightCount)
		: Object(points, countOfPoints, NULL, NULL, false, shaderPath, texturePath, true, lightCount) { }
};