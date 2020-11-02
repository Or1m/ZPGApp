#include "Object.h"
#include "Camera.h"
#include "Light.h"

Object::Object(const float points[], const int countOfPoints, unsigned int indexes[], int countOfIndexes, bool isWithIndexes, std::string& shaderPath)
:	modelMatrix(glm::mat4(1.0f)),
	points(points), countOfPoints(countOfPoints), sizeOfPoints(countOfPoints * 6 * sizeof(float)),
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
	//this->vertexArray->bind();

	if (this->hasIndexes)
		this->indexBuffer->bind();
}

void Object::useShaderProgram() const {
	this->shader->useProgram();
}

bool Object::isWithIndexes() const {
	return this->hasIndexes;
}

void Object::addLight(Light* light) {
	this->shader->addLight(light);
}

void Object::init() {
	this->shader->sendUniform("modelMatrix", this->modelMatrix);
	this->shader->sendUniform("projectionMatrix", Camera::getInstance()->getProjection());
	this->shader->sendUniform("viewMatrix", Camera::getInstance()->getCamera());
}

void Object::changeColor(glm::vec3 color) {
	this->shader->sendUniform("color", color);
}

void Object::moveTo(glm::vec3 translation) {
	this->shader->sendUniform("modelMatrix", glm::translate(glm::mat4(1.0f), translation));
}

void Object::move(glm::vec3 translation) {
	this->modelMatrix = glm::translate(modelMatrix, translation);
	this->shader->sendUniform("modelMatrix", modelMatrix);
}