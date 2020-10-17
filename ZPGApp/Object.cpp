#include "Object.h"

/**
 * Create vertex buffer object VBO  
*/
void Object::createVBO(float points[], int sizeOfPoints) {
	/*
	 * Parametre
	 * 1. -> pocet bufferov (v tomto pripade 1)
	 * 2. -> pointer na unsigned int - na tu adresu sa ulozi ID vygenerovaneho bufferu
	 */
	glGenBuffers(1, &this->VBO);
	/*
	 * Parametre
	 * 1. -> ucel bufferu (array)
	 * 2. -> ID buffer
	 */
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, 17280, points, GL_STATIC_DRAW);
}

/**
 * vertex attribute object (VAO)
*/
void Object::createVAO() {

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	/*
	 * Parametre
	 * 1.	-> index generickeho vertex atributu - layout(location=0) in vec3 vp; vo vertex shaderi ukazje ze dany atribut je na idx 0
	 * 2.	-> pocet komponentov na 1 genericky atribut teda 3 floaty (3D coordinaty) na 1 bod
	 * 3, 4 -> datovy typ, normalized - floaty uz su normalizovane
	 * 5	-> stride - velkost vertexu (o kolko bytov sa mam posunut ked chcem prejst na dalsi vertex) sizeof(float) * 3
	 * 6	-> offset - null alebo 0 v tomto pripade
	 */
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
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
