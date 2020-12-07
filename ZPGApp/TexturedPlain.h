#pragma once

#include "Object.h"
#include "Resources/Models/textured_plain.h"

class TexturedPlain : public Object {
public:
	TexturedPlain(const std::string& shaderPath, const std::string& texturePath) : TexturedPlain(shaderPath, texturePath, 1) {}
	TexturedPlain(const std::string& shaderPath, const std::string& texturePath, int lightCount) : 
		Object(texPlain, texPlaneCount, NULL, NULL, false, shaderPath, texturePath, true, lightCount) {}
	~TexturedPlain() {};
};