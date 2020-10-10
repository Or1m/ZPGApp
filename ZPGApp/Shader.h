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

	void sendUniform(const GLchar* name, glm::mat4 M4);
	void sendUniform(const GLchar* name, glm::vec4 V4);
	void sendUniform(const GLchar* name, glm::vec3 V3);
	void sendUniform(const GLchar* name, GLfloat F);
	void sendUniform(const GLchar* name, GLint I);
	void sendUniform(const GLchar* name, GLuint U);

private:
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;

	const char* vertex_shader;
	const char* fragment_shader;
};