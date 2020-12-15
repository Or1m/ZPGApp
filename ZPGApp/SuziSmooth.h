#pragma once

#include "Object.h"
#include "Resources/Models/suzi_smooth.hpp"

class SuziSmooth : public Object {
public:
	SuziSmooth(const std::string& shaderPath) : SuziSmooth(shaderPath, 1) {}
	SuziSmooth(const std::string& shaderPath, int lightCount) : Object(suziSmooth, suziSmoothCount, NULL, NULL, false, shaderPath, nullptr, false, lightCount) {}
	~SuziSmooth() {};
};