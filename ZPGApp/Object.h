#pragma once
#include "Header.h"

class Object
{
public:
	Object();
	~Object();

	void createVBO(float points[], int sizeOfPoints);
	void createVAO(unsigned int indices[]);
	void bindVertexArray();

private:
	GLuint VBO;
	GLuint VAO;

	int sizeOfPoints;
};