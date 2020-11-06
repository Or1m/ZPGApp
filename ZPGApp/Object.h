#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "TransformableObject.h"

class Object : TransformableObject {
public:
	Object(const float points[], const int countOfPoints, unsigned int indexes[], int countOfIndexes, bool isWithIndexes, const std::string& shaderPath);
	virtual ~Object();

	void bindBuffers() const;
	void useShaderProgram() const;
	bool isWithIndexes() const;

	inline int getIndexCount() const { return this->countOfIndexes; }
	inline int getVertexCount() const { return this->countOfPoints; }

	template <typename T>
	void sendUniformToShader(const GLchar* name, T t) const {
		this->shader->sendUniform(name, t);
	}

	int getID() const { return this->id; }

	void addLight(Light* light);
	void init();
	void changeColor(glm::vec3 color);
	void moveTo(glm::vec3 pos);
	void move(glm::vec3 trans);
	void scale(glm::vec3 scale);

protected:
	VertexBuffer* vertexBuffer;
	VertexBufferLayout* vertexBufferLayout;
	IndexBuffer* indexBuffer;
	VertexArray* vertexArray;
	Shader* shader;

	glm::mat4 modelMatrix;

	const float* points;
	int countOfPoints;
	int sizeOfPoints;

	unsigned int* indexes;
	int countOfIndexes;
	bool hasIndexes;

	int id;
};