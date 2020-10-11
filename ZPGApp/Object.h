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
	void bindVertexArray();

private:
	GLuint VAO;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	int sizeOfPoints;
	float* points;
};