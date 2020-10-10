#pragma once
#include "Header.h"

// pridat GLinty akoze ideèka vertex a fragmentu
class Shader
{
public:
	Shader(const char* vertex_shader, const char* fragment_shader);
	~Shader();

	void useProgram();
	GLuint compileShader(GLuint type, const char* source);
	void testLinkStatus(GLint status);
	GLuint testCompileStatus(GLint status, GLuint shaderID, GLuint type);

	void sendUniform(const GLchar* name, glm::vec3 V);
	void sendUniform(const GLchar* name, glm::mat4 M);

private:
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;

	const char* vertex_shader;
	const char* fragment_shader;
};