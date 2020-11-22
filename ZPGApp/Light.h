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
	float getCutOff() { return this->cutOff; }
	glm::vec3 getAttenuation()		{ return glm::vec3(this->constant, this->linear, this->quadratic); }
	
private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 lightColor;

	float constant;
	float linear;
	float quadratic;

	float cutOff;

	int index;
	int lightType;
};