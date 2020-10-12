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

void Renderer::draw(Object* objectToDraw) const {
	objectToDraw->bindBuffers();

	// Params - mode,first,count
	glDrawElements(GL_TRIANGLES, objectToDraw->getIndexBufferCount(), GL_UNSIGNED_INT, NULL);
}

void Renderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffer
}