#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "SOIL.h"

enum class TextureType {
	texture2D = GL_TEXTURE_2D,
	cubemap   = GL_TEXTURE_CUBE_MAP
};

class Texture {
public:
	Texture(TextureType type);
	virtual ~Texture();

	virtual void bind() const;
	void unbind();

	int getDimension()	  { return this->dimension; }
	int getSlot()		  { return this->slot; }
	TextureType getType() { return this->type; }

protected:
	unsigned int textureId;
	int dimension;
	int slot;

	TextureType type; // GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP
};