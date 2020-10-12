#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

// hovori ako velky je kazdy vertex vo vertex bufferi apod
// Vertex array spaja vertex buffer s layoutom (rozlozenim dat)
class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);

	void bind() const;
	void unbind() const;

private:
	GLuint VAO;
};

