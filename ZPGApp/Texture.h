#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "SOIL.h"

class Texture {
public:
	Texture(int type);
	virtual ~Texture();

	virtual void bind() const;
	void unbind();

	int getDimension()	{ return this->dimension; }
	int getSlot()		{ return this->slot; }

protected:
	unsigned int textureId;
	int dimension;
	int slot;

	int type; // GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP
};