#include "Cubemap.h"

Cubemap::Cubemap(const std::string paths[6]) {

	this->textureId = SOIL_load_OGL_cubemap(paths[0].c_str(), paths[1].c_str(), paths[2].c_str(),
		paths[3].c_str(), paths[4].c_str(), paths[5].c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	this->dimension = 3;
}

void Cubemap::bind() const {
	Texture::bind();

	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureId);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}