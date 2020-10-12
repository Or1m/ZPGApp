#pragma once
#include "Header.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class Object {
public:
	Object(float points[], int sizeOfPoints, unsigned int indexes[], int countOfIndexes, std::string& shaderPath);
	~Object();

	void bindBuffers();
	inline int getIndexBufferCount() const { return this->indexBuffer->getCount(); }

	template <typename T>
	void sendUniformToShader(const GLchar* name, T t) {
		this->shader->sendUniform(name, t);
	}

private:
	VertexBuffer* vertexBuffer;
	VertexBufferLayout* vertexBufferLayout;
	IndexBuffer* indexBuffer;
	VertexArray* vertexArray;

	Shader* shader;

	int sizeOfPoints;
	int countOfIndexes;
	float* points;
	unsigned int* indexes;
};