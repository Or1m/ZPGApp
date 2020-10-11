#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	/*
	 * Parametre
	 * 1. -> pocet bufferov (v tomto pripade 1)
	 * 2. -> pointer na unsigned int - na tu adresu sa ulozi ID vygenerovaneho bufferu
	 */
	glGenBuffers(1, &this->VBO);
	/*
	 * Parametre
	 * 1. -> ucel bufferu (array)
	 * 2. -> ID buffer
	 */
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &this->VBO);
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}