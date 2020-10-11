#pragma once
#include "Header.h"

// buffer s datami
class VertexBuffer {
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const; // const changes the type of this from Foo* const into const Foo* const
	void unbind() const;

private:
	GLuint VBO;
};

