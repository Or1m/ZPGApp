#include "Texture.h"
#include "SOIL.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Texture::Texture(const std::string& path) 
:	filePath(path) {

	this->textureId = SOIL_load_OGL_texture(this->filePath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (textureId == 0)
		std::cout << SOIL_last_result() << std::endl;
	/*else
		this->bind();*/
}

Texture::~Texture() {
	glDeleteTextures(1, &this->textureId);
}

void Texture::bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->textureId);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}