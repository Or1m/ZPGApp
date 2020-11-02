#pragma once

#include "Object.h"
#include "Resources/Models/suzi_smooth.h"

class SuziSmooth : public Object {
public:
	SuziSmooth(std::string& shaderPath) : Object(suziSmooth, suziSmoothCount, NULL, NULL, false, shaderPath) {}
	~SuziSmooth() {};

private:

};