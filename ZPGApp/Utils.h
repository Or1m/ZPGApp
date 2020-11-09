#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>	

#define ASSERT(x) if (!(x)) __debugbreak();

// use it like GLCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, NULL));
#define GLCall(x) glClearErrors();\
	x;\
	ASSERT(glLogCall(#x, __FILE__, __LINE__));

static bool glLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "OpenGL error with code " << error << " occurs."
			<< "\nFunction: "	<< function 
			<< "\nFile: "		<< file 
			<< "\nLine: "		<< line << "\n";
		return false;
	}

	return true;
}

static void glClearErrors() {
	while (glGetError() != GL_NO_ERROR);
}

static void glCheckError() {
	while (GLenum error = glGetError())
		std::cout << "OpenGL error: " << error << "\n";
}


static glm::vec3 fromRGB(int R, int G, int B) {
	return glm::vec3(R / 255.0f, G / 255.0f, B / 255.0f);
}


struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};