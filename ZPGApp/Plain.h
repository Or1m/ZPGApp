#pragma once

#include "Object.h"
#include "Resources/Models/plain.h"

class Plain : public Object {
public:
	Plain(std::string& shaderPath) : Object(plain, planeCount, NULL, NULL, false, shaderPath) {}
	~Plain() {};

private:

};