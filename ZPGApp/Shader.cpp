#include "Shader.h"

// Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//create and compile shaders
Shader::Shader(const char* vertex_shader, const char* fragment_shader) {
	this->vertex_shader = vertex_shader;
	this->fragment_shader = fragment_shader;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &this->vertex_shader, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &this->fragment_shader, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram(); // najdolezitejsie
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	glm::mat4 M = glm::mat4(1.0f);
	//M = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	//M = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//M = glm::rotate(M, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//M = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));

	// ... create shader
	GLint modelMatrixID = glGetUniformLocation(shaderProgram, "modelMatrix");
	//Render
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(M));
	//location, count, transpose, *value

	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

	testStatus(status);
}

void Shader::useProgram() {
	glUseProgram(shaderProgram);
}

void Shader::testStatus(GLint status) {
	
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

Shader::~Shader() {
	delete this;
}