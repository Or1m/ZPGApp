#include "Texture.h"
#include "SOIL.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static int staticSlot = 0;

Texture::Texture(const std::string& path) 
:	filePath(path), slot(staticSlot++) {

	this->textureId = SOIL_load_OGL_texture(this->filePath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (textureId == 0)
		std::cout << SOIL_last_result() << std::endl;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::~Texture() {
	glDeleteTextures(1, &this->textureId);
}

void Texture::bind() const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->textureId);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}