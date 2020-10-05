#pragma once
#include "Header.h"

// pridat GLinty akoze ideèka vertex a fragmentu
class Shader
{
public:
	Shader(const char* vertex_shader, const char* fragment_shader);
	~Shader();

	void useProgram();
	void testStatus(GLint status);
	void sendUniform(const GLchar* name, glm::vec3 V);
	void sendUniform(const GLchar* name, glm::mat4 M);

private:
	GLuint shaderProgram;
	const char* vertex_shader;
	const char* fragment_shader;
};