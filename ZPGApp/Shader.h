#pragma once

// Include GLEW
#include <GL/glew.h>

// Include the standard C++ headers  
#include <stdlib.h> // E.g. printf() and scanf()
#include <stdio.h> // E.g. malloc() and free()

class Shader
{
public:
	Shader(const char* vertex_shader, const char* fragment_shader);
	~Shader();

	void useProgram();
	void setVertexShader(const char* vertex_shader);
	void setFragmentShader(const char* fragment_shader);

private:
	GLuint shaderProgram;
	const char* vertex_shader;
	const char* fragment_shader;
};