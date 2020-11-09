#include "Object.h"
#include "Camera.h"
#include "Light.h"

#include "Move.h"

static int identificator = 1;

Object::Object(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath)
:	modelMatrix(glm::mat4(1.0f)),
	points(points), countOfPoints(countOfPoints), sizeOfPoints(countOfPoints * 6 * sizeof(float)),
	indexes(indexes), countOfIndexes(countOfIndexes), hasIndexes(isWithIndexes), id(identificator++),
	transformation(new ComplexTransformation()) {

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
	this->init();
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
	this->vertexArray->bind();

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
	this->useShaderProgram();
	this->shader->addLight(light);
}

void Object::init() {
	this->useShaderProgram();

	this->shader->sendUniform("modelMatrix", this->modelMatrix);
	this->shader->sendUniform("projectionMatrix", Camera::getInstance()->getProjection());
	this->shader->sendUniform("viewMatrix", Camera::getInstance()->getCamera());

	this->shader->sendUniform("viewPosition", Camera::getInstance()->getPosition());
}


void Object::changeColor(glm::vec3 color) {
	this->useShaderProgram();

	this->shader->sendUniform("color", color);
}


// WORK IN PROGRESS
void Object::moveTo(glm::vec3 pos) {
	this->useShaderProgram();

	// OLD
	this->modelMatrix = glm::translate(glm::mat4(1.0), pos);
	/*this->shader->sendUniform("modelMatrix", modelMatrix);*/

	// NEW
	this->transformation->add(new Move(pos));
	this->shader->sendUniform("modelMatrix", this->transformation->apply());
}

void Object::move(glm::vec3 trans) {
	this->useShaderProgram();

	this->modelMatrix = glm::translate(modelMatrix, trans);
	this->shader->sendUniform("modelMatrix", modelMatrix);
}

void Object::scale(glm::vec3 scale) {
	this->useShaderProgram();

	this->modelMatrix = glm::scale(this->modelMatrix, scale);
	this->shader->sendUniform("modelMatrix", modelMatrix);
}
