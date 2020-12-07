#include "Object.h"
#include "Camera.h"
#include "Light.h"


static int identificator = 1;

Object::Object(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath, int lightCount, bool isWithTexture)
:	points(points), countOfPoints(countOfPoints),
	indexes(indexes), countOfIndexes(countOfIndexes), hasIndexes(isWithIndexes), 
	lightCount(lightCount), id(identificator++), transformation(new ComplexTransformation()) {

	this->sizeOfPoints = isWithTexture ? countOfPoints * 8 * sizeof(float) : countOfPoints * 6 * sizeof(float);

	this->vertexArray = new VertexArray(); // creating VAO
	this->vertexBuffer = new VertexBuffer(this->points, this->sizeOfPoints); // creating VBO

	this->vertexBufferLayout = new VertexBufferLayout();
	this->vertexBufferLayout->push<float>(3); // glVertexAttribPointer(0, 3 <---)
	this->vertexBufferLayout->push<float>(3);
	if(isWithTexture)
		this->vertexBufferLayout->push<float>(2);

	this->vertexArray->addBuffer(*this->vertexBuffer, *this->vertexBufferLayout);

	
	this->indexBuffer = this->hasIndexes ? new IndexBuffer(this->indexes, this->countOfIndexes) : NULL;

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

	this->shader->sendUniform("numberOfLights", this->lightCount);
	this->shader->sendUniform("modelMatrix", glm::mat4(1.0f));
	this->shader->sendUniform("projectionMatrix", Camera::getInstance()->getProjection());
	this->shader->sendUniform("viewMatrix", Camera::getInstance()->getCamera());

	this->shader->sendUniform("viewPosition", Camera::getInstance()->getPosition());
}


void Object::changeColor(glm::vec3 color) {
	this->useShaderProgram();

	this->shader->sendUniform("color", color);
}


void Object::move(glm::vec3 trans) {
	this->useShaderProgram();

	this->shader->sendUniform("modelMatrix", this->transformation->add(new Move(trans)));
}

void Object::scale(glm::vec3 scale) {
	this->useShaderProgram();

	this->shader->sendUniform("modelMatrix", this->transformation->add(new Scale(scale)));
}