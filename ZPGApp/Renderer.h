#pragma once
#include "Header.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer {
public:
	void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
	void clear() const;
};

