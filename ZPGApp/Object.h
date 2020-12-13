#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ComplexTransformation.h"
#include "Texture2D.h"

class Object {
public:
	Object(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath, 
		bool isWithTexture = false, int lightCount = 1);

	Object(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath,
		 const std::string* texturePath, bool isWithTexture = true, int lightCount = 1);

	virtual ~Object();

	void bindBuffers() const;
	void useShaderProgram() const;
	bool isWithIndexes() const;

	inline int getIndexCount()  const { return this->countOfIndexes; }
	inline int getVertexCount() const { return this->countOfPoints; }

	template <typename T>
	void sendUniformToShader(const GLchar* name, T t) const {
		this->useShaderProgram();
		this->shader->sendUniform(name, t);
	}

	int getID() const { return this->id; }

	void addLight(Light* light);
	void init();
	void changeColor(glm::vec3 color);
	void move(glm::vec3 trans);
	void scale(glm::vec3 scale);

protected:
	VertexBuffer* vertexBuffer;
	VertexBufferLayout* vertexBufferLayout;
	IndexBuffer* indexBuffer;
	VertexArray* vertexArray;
	Shader* shader;
	ComplexTransformation* transformation;
	Texture* texture;

	const float* points;
	int countOfPoints;
	int sizeOfPoints;

	int lightCount;
	int floatsInPoint = 6;

	const unsigned int* indexes;
	int countOfIndexes;
	bool hasIndexes;
	bool hasTexture;

	int id;
};