#pragma once

#include "Texture.h"

class Texture2D : public Texture {
public:
	Texture2D(const std::string& path);
	
	void bind() const override;

private:
	std::string filePath;
};

