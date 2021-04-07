#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>			// glm::value_ptr
#include <glm/gtx/string_cast.hpp>		// glm::to_string()

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


static float bazierMatrix[] = {
	   -1,  3, -3,  1,
		3, -6,  3,  0,
	   -3,  3,  0,  0,
		1,  0,  0,  0
};

static glm::vec3 calcBazier(float t, glm::vec3* arr) {

	glm::vec4 vec = glm::vec4(t * t * t, t * t, t, 1);
	glm::mat4x3 points = glm::mat4x3(arr[0], arr[1], arr[2], arr[3]);

	glm::vec3 pos = vec * glm::make_mat4(bazierMatrix) * points;

	return pos;
}

const int MAX = 8;
static int visited[MAX];

static int randomWithoutRepetition() {
	srand((unsigned int)time((time_t*)NULL));
	
	int i = 0, num = 0;
	while (i < MAX) {
		num = rand() % MAX;

		if (visited[num] == 0) {
			visited[num] = 1;

			return num;
		}
	}
}

static void clearVisited() {
	for (int i = 0; i < MAX; i++)
	{
		visited[i] = 0;
	}
}