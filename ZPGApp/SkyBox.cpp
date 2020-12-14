#include "SkyBox.h"
#include "Camera.h"

#include<string>

const std::string defaultFiles[] = {
	"Resources/Textures/negx.jpg",
	"Resources/Textures/posx.jpg",
	"Resources/Textures/posy.jpg",
	"Resources/Textures/negy.jpg",
	"Resources/Textures/negz.jpg",
	"Resources/Textures/posz.jpg"
};

SkyBox::SkyBox(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath) 
:	SkyBox(points, countOfPoints, indexes, countOfIndexes, isWithIndexes, shaderPath, 1) { }

SkyBox::SkyBox(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath, int lightCount)
:	Object(points, countOfPoints, indexes, countOfIndexes, isWithIndexes, shaderPath, defaultFiles, true, true, lightCount) { }

SkyBox::~SkyBox() { }

void SkyBox::bindBuffers() const {
	glDepthMask(GL_FALSE);

	Object::bindBuffers();
}