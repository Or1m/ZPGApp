#pragma once

#include "Object.h"

class Terrain : public Object {
public:
	Terrain(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath);
	~Terrain() { }
};