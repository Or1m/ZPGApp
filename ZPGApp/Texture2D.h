#pragma once

#include "Texture.h"

class Texture2D : public Texture {
public:
	Texture2D(const std::string& path);

private:
	std::string filePath;
};

