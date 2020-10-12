#include "Object.h"


Object::Object(float points[], int sizeOfPoints, unsigned int indexes[], int countOfIndexes, std::string& shaderPath) {
	this->sizeOfPoints = sizeOfPoints;
	this->points = points;
	this->indexes = indexes;
	this->countOfIndexes = countOfIndexes;

	this->vertexArray = new VertexArray();// creating VAO
	this->vertexBuffer = new VertexBuffer(this->points, this->sizeOfPoints); // creating VBO

	this->vertexBufferLayout = new VertexBufferLayout();
	this->vertexBufferLayout->push<float>(3); // glVertexAttribPointer(0, 3 <---)

	this->vertexArray->addBuffer(*this->vertexBuffer, *this->vertexBufferLayout);
	this->indexBuffer = new IndexBuffer(this->indexes, this->countOfIndexes);

	this->shader = new Shader(shaderPath);
}

Object::~Object() {
	delete this->vertexBuffer;
	delete this->indexBuffer;

	delete this;
}

void Object::bindVertexArray() {

	vertexBuffer->bind();
	indexBuffer->bind();
}

Shader* Object::getShader() {
	return this->shader;
}

IndexBuffer* Object::getIndexBuffer() {
	return this->indexBuffer;
}
VertexArray* Object::getVertexArray() {
	return this->vertexArray;
}