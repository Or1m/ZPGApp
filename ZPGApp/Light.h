#pragma once
#include <glm\ext\vector_float3.hpp>

#include <vector>

#include "Subject.h"

enum class LightType {
	pointLight,
	directionalLight,
	spotLight
};


class Light : public Subject {
public:
	Light(LightType type);
	~Light() {}

	glm::vec3 getLightColor()	{ return this->lightColor; }
	int getIndex()				{ return this->index; }
	LightType getType()			{ return this->type; }
	
private:
	LightType type;
	glm::vec3 lightColor;
	int index;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};