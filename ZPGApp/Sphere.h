#pragma once

#include "Object.h"
#include "Resources/Models/sphere.h"

class Sphere : public Object {
public:
	Sphere(const std::string& shaderPath) : Sphere(shaderPath, 1) {}
	Sphere(const std::string& shaderPath, int lightCount) : Object(sphere, sphereCount, NULL, NULL, false, shaderPath, lightCount) {}
	~Sphere() {};
};