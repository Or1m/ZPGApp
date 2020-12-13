#pragma once

#include "Object.h"

class SkyBox : public Object {
public:
	SkyBox(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath);
	~SkyBox();

	void bindBuffers() const override;
};