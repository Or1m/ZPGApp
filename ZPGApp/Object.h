#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ComplexTransformation.h"

#include "Texture.h"

class Object {
public:
	Object(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath,
		 const std::string* texturePath = nullptr, bool isWithTexture = true, int lightCount = 1);

	Object(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath,
		const std::string paths[6], bool sky = true, bool isWithTexture = true, int lightCount = 1);

	virtual ~Object();


	void init(const std::string& shaderPath);
	void initValues();

	virtual void bindBuffers()	const;
	void useShaderProgram()		const;
	bool isWithIndexes()		const;

	inline int getID()			const { return this->id; }
	inline int getIndexCount()  const { return this->countOfIndexes; }
	inline int getVertexCount() const { return this->countOfPoints;  }


	template <typename T>
	void sendUniformToShader(const GLchar* name, T t) const {
		this->useShaderProgram();
		this->shader->sendUniform(name, t);
	}

	
	void addLight(Light* light);
	
	void changeColor(glm::vec3 color);

	void move(glm::vec3 trans);
	void moveTo(glm::vec3 pos);
	void scale(glm::vec3 scale);
	void rotate(float angle, glm::vec3 direction);

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