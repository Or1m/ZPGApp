#include "Renderer.h"

Renderer* Renderer::instance = NULL;

Renderer* Renderer::getInstance() {
	if (instance == NULL) {
		instance = new Renderer();
	}

	return instance;
}

Renderer::Renderer() {}

Renderer::~Renderer() {
	delete this;
}

void Renderer::draw(const Object& objectToDraw) const {
	objectToDraw.bindBuffers();

	if(objectToDraw.isWithIndexes())
		glDrawElements(GL_TRIANGLES, objectToDraw.getIndexCount(), GL_UNSIGNED_INT, NULL); // Params - mode,first,count
	else
		glDrawArrays(GL_TRIANGLES, 0, objectToDraw.getVertexCount());
}

void Renderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffer
}