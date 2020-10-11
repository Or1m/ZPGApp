#pragma once
#include "Header.h"

class VertexBuffer {
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind();
	void unbind();

private:
	GLuint VBO;
};

