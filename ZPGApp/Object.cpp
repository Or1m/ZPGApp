#include "Object.h"

//vertex buffer object (VBO)
void Object::createVBO(float points[], int sizeOfPoints) {

	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeOfPoints, points, GL_STATIC_DRAW);
}

//vertex attribute object (VAO)
void Object::createVAO() {

	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes // suvisi s layout(location=0) in vec3 vp; vo vertex shaderi
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Object::bindVertexArray() {
	glBindVertexArray(VAO);
}

Object::Object() {
	VBO = 0;
	VAO = 0;
}

Object::~Object() {
	delete this;
}
