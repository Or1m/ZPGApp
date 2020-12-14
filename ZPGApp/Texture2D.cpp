#include "Texture2D.h"

Texture2D::Texture2D(const std::string& path) : Texture(GL_TEXTURE_2D) {

	this->filePath = path;
	this->textureId = SOIL_load_OGL_texture(this->filePath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (textureId == 0)
		std::cout << SOIL_last_result() << std::endl;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}