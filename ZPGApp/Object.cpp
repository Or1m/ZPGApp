#include "Object.h"

Object::Object(float points[], int sizeOfPoints, unsigned int indexes[], int countOfIndexes, bool isWithIndexes, std::string& shaderPath) {
	this->sizeOfPoints = sizeOfPoints;
	this->points = points;
	this->indexes = indexes;
	this->countOfIndexes = countOfIndexes;
	this->hasIndexes = isWithIndexes;

	this->vertexArray = new VertexArray();// creating VAO
	this->vertexBuffer = new VertexBuffer(this->points, this->sizeOfPoints); // creating VBO

	this->vertexBufferLayout = new VertexBufferLayout();
	this->vertexBufferLayout->push<float>(3); // glVertexAttribPointer(0, 3 <---)

	this->vertexArray->addBuffer(*this->vertexBuffer, *this->vertexBufferLayout);

	if (!this->hasIndexes)
		this->indexBuffer = NULL;
	else
		this->indexBuffer = new IndexBuffer(this->indexes, this->countOfIndexes);

	this->shader = new Shader(shaderPath);
}

Object::~Object() {
	delete this->vertexBuffer;
	delete this->indexBuffer;

	delete this;
}

void Object::bindBuffers() {
	this->shader->useProgram();
	this->vertexBuffer->bind();

	if (this->hasIndexes)
		this->indexBuffer->bind();
}

void Object::useShaderProgram() {
	this->shader->useProgram();
}

bool Object::isWithIndexes() {
	return this->hasIndexes;
}