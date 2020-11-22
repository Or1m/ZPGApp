#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>		
#include <glm/vec4.hpp>		
#include <glm/mat4x4.hpp>	
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string>
#include <sstream>

#include "Utils.h"
#include "Observer.h"


class Shader : Observer {
public:
	Shader(const std::string& filePath);
	~Shader();

	void useProgram() const;
	void unbindProgram() const;

	void update(Camera& camera) override;
	void update(Light& light, int idx) override;

	void addLight(Light* light);

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