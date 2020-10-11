#pragma once
#include "Header.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Object {
public:
	Object();
	~Object();

	void createVBO(float points[], int sizeOfPoints);
	void createVAO(unsigned int indices[]);
	void createIBO(unsigned int indices[]);
	void bindVertexArray();

private:
	GLuint VBO;
	GLuint VAO;
	GLuint IBO;

	VertexBuffer* vertex;
	IndexBuffer* index;

	int sizeOfPoints;
	float* points;
};