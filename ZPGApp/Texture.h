#pragma once

#include "Renderer.h"

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind();

	int getWidth()	const { return this->width; }
	int getHeight() const { return this->height; }

private:
	unsigned int textureId;
	std::string filePath;
	unsigned char* localBuffer;
	
	int width;
	int height;
	int bitsPerPixel;
};