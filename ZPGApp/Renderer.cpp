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

	if(objectToDraw->isWithIndexes())
		glDrawElements(GL_TRIANGLES, objectToDraw->getIndexBufferCount(), GL_UNSIGNED_INT, NULL); // Params - mode,first,count
	else
		glDrawArrays(GL_TRIANGLES, 0, 3); // bacha nahardcodene 3 vertexy
}

void Renderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffer
}