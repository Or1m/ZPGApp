#pragma once

// Include GLEW
#include <GL/glew.h>

// Include GLFW 
#include <GLFW/glfw3.h>

// Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp> // glm::to_string()

// Include the standard C++ headers  
#include <stdlib.h> // E.g. printf() and scanf()
#include <stdio.h> // E.g. malloc() and free()
#include <iostream>

struct WindowOptions
{
	int windowWidth; 
	int windowHeight; 
	const char* windowTitle;

	WindowOptions(int windowWidth, int windowHeight, const char* windowTitle) {
		this->windowWidth = windowWidth;
		this->windowHeight = windowHeight;
		this->windowTitle = windowTitle;
	}
};

struct Shaders
{
	const char* vertex_shader;
	const char* fragment_shader;

	Shaders() {
		vertex_shader = NULL;
		fragment_shader = NULL;
	}

	Shaders(const char* vertex_shader, const char* fragment_shader) {
		this->vertex_shader = vertex_shader;
		this->fragment_shader = fragment_shader;
	}
};