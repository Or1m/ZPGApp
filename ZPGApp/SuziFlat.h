#pragma once

#include "Object.h"
#include "Resources/Models/suzi_flat.h"

class SuziFlat : public Object {
public:
	SuziFlat(std::string& shaderPath) : Object(suziFlat, suziFlatCount, NULL, NULL, false, shaderPath) {}
	~SuziFlat() {};

private:

};