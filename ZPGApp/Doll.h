#pragma once

#include "Object.h"

class Doll : public Object {
public:
	Doll(const float points[], const int countOfPoints, const std::string& shaderPath, const std::string* texturePath, int lightCount)
		: Object(points, countOfPoints, NULL, NULL, false, shaderPath, texturePath, true, lightCount) { }
};