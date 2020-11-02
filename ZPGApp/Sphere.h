#pragma once

#include "Object.h"
#include "Resources/Models/sphere.h"

class Sphere : public Object {
public:
	Sphere(const std::string& shaderPath) : Object(sphere, sphereCount, NULL, NULL, false, shaderPath) {}
	~Sphere() {};
};