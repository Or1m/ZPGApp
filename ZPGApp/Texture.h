#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind();

	//int getDimension() { return this->dimension; }

private:
	unsigned int textureId;
	int dimension = 2;

	std::string filePath;
};