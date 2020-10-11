#pragma once
#include "Header.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

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
	VertexArray* vertexArray;
	VertexBufferLayout* vertexBufferLayout;

	int sizeOfPoints;
	float* points;
};