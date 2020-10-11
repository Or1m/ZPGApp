#include "Object.h"

/**
 * Create vertex buffer object VBO  
*/
void Object::createVBO(float points[], int sizeOfPoints) {
	this->sizeOfPoints = sizeOfPoints;
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
	glBufferData(GL_ARRAY_BUFFER, sizeOfPoints, points, GL_STATIC_DRAW);
}

/**
 * vertex attribute object (VAO)
*/
void Object::createVAO(unsigned int indices[]) {

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	/*
	 * Linkuje array buffer object s VAO, potom vo vykreslovacej smycke staci volat bind VAO a netreba bindovat ostatne veci
	 * Parametre
	 * 1.	-> index generickeho vertex atributu - layout(location=0) in vec3 vp; vo vertex shaderi ukazje ze dany atribut je na idx 0
	 * 2.	-> pocet komponentov na 1 genericky atribut teda 3 floaty (3D coordinaty) na 1 bod
	 * 3, 4 -> datovy typ, normalized - floaty uz su normalizovane
	 * 5	-> stride - velkost vertexu (o kolko bytov sa mam posunut ked chcem prejst na dalsi vertex) sizeof(float) * 3
	 * 6	-> offset - null alebo 0 v tomto pripade
	 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	createIBO(indices);
}

void Object::createIBO(unsigned int indices[]) {

	glGenBuffers(1, &this->IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void Object::bindVertexArray() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
}

Object::Object() {
	this->VBO = 0;
	this->VAO = 0;

	this->sizeOfPoints = -1;
}

Object::~Object() {
	delete this;
}
