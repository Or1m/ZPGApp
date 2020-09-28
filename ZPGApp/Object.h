#pragma once

// Include GLEW
#include <GL/glew.h>

// Include the standard C++ headers  
#include <stdlib.h> // E.g. printf() and scanf()
#include <stdio.h> // E.g. malloc() and free()

class Object
{
public:
	void createVBO(float points[]);
	void createVAO();

private:
	GLuint VBO;
	GLuint VAO;
};