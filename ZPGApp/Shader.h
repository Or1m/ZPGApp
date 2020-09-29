#pragma once

// Include GLEW
#include <GL/glew.h>

// Include the standard C++ headers  
#include <stdlib.h> // E.g. printf() and scanf()
#include <stdio.h> // E.g. malloc() and free()

// pridat GLinty akoze ideèka vertex a fragmentu
class Shader
{
public:
	Shader(const char* vertex_shader, const char* fragment_shader);
	~Shader();

	void useProgram();
	void testStatus(GLint status);

private:
	GLuint shaderProgram;
	const char* vertex_shader;
	const char* fragment_shader;
};