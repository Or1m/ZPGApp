#pragma once

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