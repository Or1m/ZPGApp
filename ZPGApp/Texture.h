#pragma once

#include <string>
#include <iostream>

#include "SOIL.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Texture {
public:
	Texture();
	~Texture();

	virtual void bind() const;
	void unbind();

	int getDimension()	{ return this->dimension; }
	int getSlot()		{ return this->slot; }

protected:
	unsigned int textureId;
	int dimension;
	int slot;
};