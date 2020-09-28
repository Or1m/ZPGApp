#pragma once

// Include GLEW
#include <GL/glew.h>

// Include the standard C++ headers  
#include <stdlib.h> // E.g. printf() and scanf()
#include <stdio.h> // E.g. malloc() and free()

class Object
{
public:
	Object();
	~Object();

	void createVBO(float points[], int sizeOfPoints);
	void createVAO();
	void bindVertexArray();

private:
	GLuint VBO;
	GLuint VAO;
};