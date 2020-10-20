#include "VertexBuffer.h"

/*
 * As of now we stored the vertex data within memory on the graphics card as managed by a vertex buffer object named VBO.
 */
VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	/**
	 * Create object and store reference for it
	 * 
	 * @param 1 pocet bufferov (v tomto pripade 1)
	 * @param 2 pointer na unsigned int - na tu adresu sa ulozi ID vygenerovaneho bufferu
	 */
	glGenBuffers(1, &this->VBO);

	/**
	 * Bind/assign object to context
	 * @param 1 ucel bufferu (array)
	 * @param 2 ID buffer
	 */
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	/*
	 * Copies the previously defined vertex data into the buffer's memory.
	 * Copy user-defined data into the currently bound buffer.
	 * 
	 * @param 1 type of the buffer we want to copy data into: the vertex buffer object currently bound to the GL_ARRAY_BUFFER target.
	 * @param 2 size of the data (in bytes) we want to pass to the buffer
	 * @param 3 data to send
	 * @param 4 how we want the graphics card to manage the given data:
	 *			GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
	 *			GL_STATIC_DRAW: the data is set only once and used many times.
	 *			GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
	 */
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