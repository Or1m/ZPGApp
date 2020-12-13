#include "Texture.h"

static int staticSlot = 0;

Texture::Texture() 
:	textureId(0), dimension(0), slot(staticSlot++) { }

Texture::~Texture() {
	glDeleteTextures(1, &this->textureId);
}

void Texture::bind() const {
	glActiveTexture(GL_TEXTURE0 + slot);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}