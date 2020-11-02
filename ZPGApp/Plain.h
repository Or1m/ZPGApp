#pragma once

#include "Object.h"
#include "Resources/Models/plain.h"

class Plain : public Object {
public:
	Plain(const std::string& shaderPath) : Object(plain, planeCount, NULL, NULL, false, shaderPath) {}
	~Plain() {};
};