#include "Texture.h"

#include "Vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path) 
:	textureId(0), filePath(path), localBuffer(nullptr), width(0), height(0), bitsPerPixel(0) {

	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(this->filePath.c_str(), &this->width, &this->height, &this->bitsPerPixel, 4);

	GLCall(glGenTextures(1, &textureId));
	GLCall(glBindTexture(GL_TEXTURE_2D, textureId));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (this->localBuffer)
		stbi_image_free(this->localBuffer);
}

Texture::~Texture() {
	GLCall(glDeleteTextures(1, &this->textureId));
}

void Texture::bind(unsigned int slot) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, this->textureId));
}

void Texture::unbind() {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}