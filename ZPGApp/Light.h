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

	void setColor(glm::vec3 color)		 { this->lightColor = color;  }
	void setAmbient(glm::vec3 ambient)	 { this->ambient = ambient;	  }
	void setDiffuse(glm::vec3 diffuse)	 { this->diffuse = diffuse;	  }
	void setSpecular(glm::vec3 specular) { this->specular = specular; }
	
private:
	LightType type;
	glm::vec3 lightColor;
	int index;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};