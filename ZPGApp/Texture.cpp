#include "Texture.h"

static int staticSlot = 0;

Texture::Texture(TextureType type)
:	textureId(0), dimension(2), slot(staticSlot++), type(type) { }

Texture::~Texture() {
	glDeleteTextures(1, &this->textureId);
}


void Texture::bind() const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture((int)type, this->textureId);
}

void Texture::unbind() {
	glBindTexture((int)type, 0);
}