#pragma once

#include <GL/glew.h>

class IndexBuffer {
public:
	IndexBuffer(const unsigned int* data, unsigned int count); // size = bytes, count = number of them
	~IndexBuffer();

	void bind()   const;
	void unbind() const;

	inline unsigned int getCount() const { return count; }

private:
	GLuint IBO;
	unsigned int count;
};

