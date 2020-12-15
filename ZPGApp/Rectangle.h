#pragma once

#include "Object.h"
#include "Resources/Models/indexed_rectangle.hpp"

class Rectangle : public Object {
public:

	Rectangle(const std::string& shaderPath) : Rectangle(shaderPath, 1) { }

	Rectangle(const std::string& shaderPath, int lightCount) : Object(rectangle, rectangleCount, rectangleIndex, rectangleIndexCount, true, shaderPath, nullptr, false, lightCount) { }

	~Rectangle() {};
};