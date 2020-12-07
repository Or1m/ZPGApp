#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void bind() const;
	void unbind();

	int getDimension()	{ return this->dimension; }
	int getSlot()		{ return this->slot; }

private:
	unsigned int textureId;
	int dimension = 2;
	int slot;

	std::string filePath;
};