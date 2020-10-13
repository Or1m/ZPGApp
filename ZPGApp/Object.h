#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class Object {
public:
	Object(float points[], int sizeOfPoints, unsigned int indexes[], int countOfIndexes, bool isWithIndexes, std::string& shaderPath);
	~Object();

	void bindBuffers() const;
	void useShaderProgram() const;
	inline int getIndexBufferCount() const { return this->indexBuffer->getCount(); }
	bool isWithIndexes() const;

	template <typename T>
	void sendUniformToShader(const GLchar* name, T t) const {
		this->shader->sendUniform(name, t);
	}

private:
	VertexBuffer* vertexBuffer;
	VertexBufferLayout* vertexBufferLayout;
	IndexBuffer* indexBuffer;
	VertexArray* vertexArray;

	Shader* shader;

	float* points;
	int sizeOfPoints;

	unsigned int* indexes;
	int countOfIndexes;
	bool hasIndexes;
};