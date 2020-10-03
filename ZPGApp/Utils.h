#pragma once
#include "Header.h"

void clearError() {
	while (glGetError() != GL_NO_ERROR);
}

void checkError() {
	while (GLenum error = glGetError()) {
		std::cout << "OpenGL error: " << error << "\n";
	}

	std::cout << "No error\n";
}