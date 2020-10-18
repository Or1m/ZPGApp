#include "Object.h"

Object::Object(const float points[], int countOfPoints, unsigned int indexes[], int countOfIndexes, bool isWithIndexes, std::string& shaderPath) 
:	points(points), countOfPoints(countOfPoints), sizeOfPoints(countOfPoints * 6 * sizeof(float)),
	indexes(indexes), countOfIndexes(countOfIndexes), hasIndexes(isWithIndexes) {

	this->vertexArray = new VertexArray(); // creating VAO
	this->vertexBuffer = new VertexBuffer(this->points, this->sizeOfPoints); // creating VBO

	this->vertexBufferLayout = new VertexBufferLayout();
	this->vertexBufferLayout->push<float>(3); // glVertexAttribPointer(0, 3 <---)
	this->vertexBufferLayout->push<float>(3);

	this->vertexArray->addBuffer(*this->vertexBuffer, *this->vertexBufferLayout);

	if (!this->hasIndexes)
		this->indexBuffer = NULL;
	else
		this->indexBuffer = new IndexBuffer(this->indexes, this->countOfIndexes);

	this->shader = new Shader(shaderPath);
}

Object::~Object() {
	delete this->vertexArray;
	delete this->vertexBuffer;
	delete this->vertexBufferLayout;
	delete this->indexBuffer;
}

void Object::bindBuffers() const {
	this->shader->useProgram();
	this->vertexBuffer->bind();

	if (this->hasIndexes)
		this->indexBuffer->bind();
}

void Object::useShaderProgram() const {
	this->shader->useProgram();
}

bool Object::isWithIndexes() const {
	return this->hasIndexes;
}