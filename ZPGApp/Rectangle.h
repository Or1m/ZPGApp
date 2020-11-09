#pragma once

#include "Object.h"
#include "Resources/Models/indexed_rectangle.h"

class Rectangle : public Object {
public:

	Rectangle(const std::string& shaderPath) : Object(rectangle, rectangleCount, rectangleIndex, rectangleIndexCount, true, shaderPath) {}
	~Rectangle() {};
};