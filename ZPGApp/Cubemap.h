#pragma once

#include "Texture.h"

class Cubemap : public Texture {
public:
	Cubemap(std::string  paths[6]);

	void bind() const override;
};

