#include "VertexArray.h"

VertexArray::VertexArray() {
}

VertexArray::~VertexArray() {
}

/*
 * glVertexAttribPointer() Linkuje array buffer object s VAO, potom vo vykreslovacej smycke staci volat 
 * bind VAO a netreba bindovat ostatne veci, viac vo videu o VA
 * Parametre
 * 1.	-> index generickeho vertex atributu - layout(location=0) in vec3 vp; vo vertex shaderi ukazje ze dany atribut je na idx 0
 * 2.	-> pocet komponentov na 1 genericky atribut teda 3 floaty (3D coordinaty) na 1 bod
 * 3, 4 -> datovy typ, normalized - floaty uz su normalizovane
 * 5	-> stride - velkost vertexu (o kolko bytov sa mam posunut ked chcem prejst na dalsi vertex) sizeof(float) * 3
 * 6	-> offset - null alebo 0 v tomto pripade
 */
void VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) {
	vertexBuffer.bind();

	const auto& elements = layout.getElements();
	unsigned int offset = 0;

	unsigned int elemSize = elements.size();
	for (unsigned int i = 0; i < elemSize; i++) {
		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL)
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset); 
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}
