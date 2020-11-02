#pragma once

#include "Object.h"
#include "Resources/Models/sphere.h"

class Sphere : public Object {
public:
	Sphere(std::string& shaderPath) : Object(sphere, sphereCount, NULL, NULL, false, shaderPath) {}
	~Sphere() {};

private:

};