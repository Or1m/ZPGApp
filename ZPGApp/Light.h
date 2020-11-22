#pragma once
#include <glm\ext\vector_float3.hpp>

#include <vector>

#include "Subject.h"


class Light : public Subject {
public:
	Light();
	Light(int type);
	~Light() {}

	void moveTo(glm::vec3 pos);
	void move(glm::vec3 trans);
	void setDirection(glm::vec3 dir);

	glm::vec3 getLightPosition()	{ return this->position; }
	glm::vec3 getLightDirection()	{ return this->direction; }
	glm::vec3 getLightColor()		{ return this->lightColor; }
	int getType()					{ return this->lightType; }
	int getIndex()					{ return this->index; }

private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 lightColor;

	int index;
	int lightType;
};