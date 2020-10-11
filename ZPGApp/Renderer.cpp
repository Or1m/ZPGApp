#include "Renderer.h"

void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const {
	shader.useProgram();
	vertexArray.bind();
	indexBuffer.bind();

	// Params - mode,first,count
	glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, NULL);
}

void Renderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffer
}
