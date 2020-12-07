#include "Object.h"
#include "Camera.h"
#include "Light.h"

//#include "Vendor/objloader.h"

static int identificator = 1;

Object::Object(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath,
	bool isWithTexture, int lightCount)
:	points(points), countOfPoints(countOfPoints),
	indexes(indexes), countOfIndexes(countOfIndexes), hasIndexes(isWithIndexes), hasTexture(isWithTexture),
	lightCount(lightCount), id(identificator++), transformation(new ComplexTransformation()) {

	this->sizeOfPoints = countOfPoints * floatsInPoint * sizeof(float);

	this->vertexArray = new VertexArray(); // creating VAO
	this->vertexBuffer = new VertexBuffer(this->points, this->sizeOfPoints); // creating VBO

	this->vertexBufferLayout = new VertexBufferLayout();
	this->vertexBufferLayout->push<float>(3); // glVertexAttribPointer(0, 3 <---)
	this->vertexBufferLayout->push<float>(3);

	this->vertexArray->addBuffer(*this->vertexBuffer, *this->vertexBufferLayout);


	this->indexBuffer = this->hasIndexes ? new IndexBuffer(this->indexes, this->countOfIndexes) : NULL;

	this->shader = new Shader(shaderPath);
	this->init();
}

Object::Object(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath,
	const std::string& texturePath, bool isWithTexture, int lightCount)
:	points(points), countOfPoints(countOfPoints),
	indexes(indexes), countOfIndexes(countOfIndexes), hasIndexes(isWithIndexes), hasTexture(isWithTexture),
	lightCount(lightCount), id(identificator++), transformation(new ComplexTransformation()) {

	if (this->hasTexture) {
		this->texture = new Texture(texturePath);
		this->floatsInPoint += this->texture->getDimension();
	}

	this->sizeOfPoints = countOfPoints * floatsInPoint * sizeof(float);

	this->vertexArray = new VertexArray(); // creating VAO
	this->vertexBuffer = new VertexBuffer(this->points, this->sizeOfPoints); // creating VBO

	this->vertexBufferLayout = new VertexBufferLayout();
	this->vertexBufferLayout->push<float>(3); // glVertexAttribPointer(0, 3 <---)
	this->vertexBufferLayout->push<float>(3);

	if(this->hasTexture)
		this->vertexBufferLayout->push<float>(this->texture->getDimension());

	this->vertexArray->addBuffer(*this->vertexBuffer, *this->vertexBufferLayout);

	
	this->indexBuffer = this->hasIndexes ? new IndexBuffer(this->indexes, this->countOfIndexes) : NULL;

	this->shader = new Shader(shaderPath);
	this->init();
}

Object::Object(const std::string& shaderPath, const std::string& texturePath, const std::string& modelPath) {
	/*std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	loadOBJ(modelPath.c_str(), vertices, uvs, normals);

	int count = vertices.size();
	int size = count * 8;

	float* arr = new float[size];

	for (int i = 0, j = 0; i < size; i += 8, j += 1) {
		arr[i + 0] = vertices[j].x;
		arr[i + 1] = vertices[j].y;
		arr[i + 2] = vertices[j].z;

		arr[i + 3] = normals[j].x;
		arr[i + 4] = normals[j].y;
		arr[i + 5] = normals[j].z;

		arr[i + 6] = uvs[j].x;
		arr[i + 7] = uvs[j].y;
	}

	Object(arr, count, NULL, NULL, false, shaderPath, texturePath);*/

	//Object::Object(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string & shaderPath,
	//const std::string & texturePath, bool isWithTexture, int lightCount)
	

	/*for (int i = 0; i < size; i += 8) {
		std::cout << arr[i + 0] << arr[i + 1] << arr[i + 2] << " || " << arr[i + 3] << arr[i + 4] << arr[i + 5] << " || " << arr[i + 6] << arr[i + 7] << std::endl;
	}*/

	/*glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	objects->push_back(new Object(&vertices[0], sphereCount, NULL, NULL, false, phongPath, 1));*/
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

	if(this->hasTexture)
		this->texture->bind();
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

	if (this->hasTexture) {
		this->shader->sendUniform("myTexture", this->texture->getSlot());
		this->shader->sendUniform("hasTexture", 1);
	}
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