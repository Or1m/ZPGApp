#pragma once

#include "Object.h"
#include "Resources/Models/suzi_flat.hpp"

class SuziFlat : public Object {
public:
	SuziFlat(const std::string& shaderPath) : SuziFlat(shaderPath, 1) { }

	SuziFlat(const std::string& shaderPath, int lightCount) : Object(suziFlat, suziFlatCount, NULL, NULL, false, shaderPath, nullptr, false, lightCount) {}

	~SuziFlat() {};
};