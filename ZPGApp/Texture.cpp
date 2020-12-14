#include "Texture.h"

static int staticSlot = 0;

Texture::Texture(int type)
:	textureId(0), dimension(2), slot(staticSlot++), type(type) { }

Texture::~Texture() {
	glDeleteTextures(1, &this->textureId);
}


void Texture::bind() const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(type, this->textureId);
}

void Texture::unbind() {
	glBindTexture(type, 0);
}