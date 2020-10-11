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

	IndexBuffer* indexBuffer; // docasne
	VertexArray* vertexArray;

private:
	GLuint VAO;

	VertexBuffer* vertexBuffer;
	
	VertexBufferLayout* vertexBufferLayout;

	int sizeOfPoints;
	float* points;
};