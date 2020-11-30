#pragma once

#include "Object.h"
#include "Resources/Models/textured_plain.h"

class TexturedPlain : public Object {
public:
	TexturedPlain(const std::string& shaderPath) : TexturedPlain(shaderPath, 1) {}
	TexturedPlain(const std::string& shaderPath, int lightCount) : Object(texPlain, texPlaneCount, NULL, NULL, false, shaderPath, lightCount, true) {}
	~TexturedPlain() {};
};