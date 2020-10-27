#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <fstream>
#include <string>
#include <sstream>

#include "Utils.h"
#include "IObserver.h"


class Shader : IObserver {
public:
	Shader(const std::string& filePath);
	~Shader();

	void useProgram() const;
	void unbindProgram() const;

	void update(Camera& camera);

	void sendUniform(const GLchar* name, glm::mat4 M4) const;
	void sendUniform(const GLchar* name, glm::vec4 V4) const;
	void sendUniform(const GLchar* name, glm::vec3 V3) const;
	void sendUniform(const GLchar* name, GLfloat F) const;
	void sendUniform(const GLchar* name, GLint I) const;
	void sendUniform(const GLchar* name, GLuint U) const;

private:
	std::string filePath;

	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;

	const char* vertexShaderSource;
	const char* fragmentShaderSource;

	ShaderProgramSource parseShader();
	void createShader();
	GLuint compileShader(GLuint type, const char* source);

	GLuint testCompileStatus(GLint status, GLuint shaderID, GLuint type);
	void testLinkStatus(GLint status);
};