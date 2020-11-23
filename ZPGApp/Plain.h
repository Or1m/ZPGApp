#pragma once

#include "Object.h"
#include "Resources/Models/plain.h"

class Plain : public Object {
public:
	Plain(const std::string& shaderPath) : Plain(shaderPath, 1) {}
	Plain(const std::string& shaderPath, int lightCount) : Object(plain, planeCount, NULL, NULL, false, shaderPath, lightCount) {}
	~Plain() {};
};