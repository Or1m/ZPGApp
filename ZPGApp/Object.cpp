#include "Object.h"


void Object::createVBO(float points[], int sizeOfPoints) {
	this->sizeOfPoints = sizeOfPoints;
	this->points = points;
}

// hovori ako velky je kazdy vertex vo vertex bufferi apod
// Vertex array spaja vertex buffer s layoutom (rozlozenim dat)
void Object::createVAO(unsigned int indices[]) {

	/*glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);*/

	this->vertexArray = new VertexArray();
	this->vertexBuffer = new VertexBuffer(this->points, this->sizeOfPoints);
	this->vertexBufferLayout = new VertexBufferLayout();

	this->vertexBufferLayout->push<float>(3); // glVertexAttribPointer(0, 3 <---)
	this->vertexArray->addBuffer(*this->vertexBuffer, *this->vertexBufferLayout);
	

	//glEnableVertexAttribArray(0); 
	////glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	///*
	// * Linkuje array buffer object s VAO, potom vo vykreslovacej smycke staci volat bind VAO a netreba bindovat ostatne veci, viac vo videu o VA
	// * Parametre
	// * 1.	-> index generickeho vertex atributu - layout(location=0) in vec3 vp; vo vertex shaderi ukazje ze dany atribut je na idx 0
	// * 2.	-> pocet komponentov na 1 genericky atribut teda 3 floaty (3D coordinaty) na 1 bod
	// * 3, 4 -> datovy typ, normalized - floaty uz su normalizovane
	// * 5	-> stride - velkost vertexu (o kolko bytov sa mam posunut ked chcem prejst na dalsi vertex) sizeof(float) * 3
	// * 6	-> offset - null alebo 0 v tomto pripade
	// */
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	this->indexBuffer = new IndexBuffer(indices, 6);
}

void Object::bindVertexArray() {

	vertexBuffer->bind();
	indexBuffer->bind();
}

Object::Object() {

	this->sizeOfPoints = -1;
}

Object::~Object() {
	delete this->vertexBuffer;
	delete this->indexBuffer;

	delete this;
}
