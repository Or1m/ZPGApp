#pragma once
#include "Header.h"

class Object
{
public:
	Object();
	~Object();

	void createVBO(float points[], int sizeOfPoints);
	void createVAO();
	void bindVertexArray();

private:
	GLuint VBO;
	GLuint VAO;
};