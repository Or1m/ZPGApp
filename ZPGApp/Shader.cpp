#include "Shader.h"

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

	this->shaderProgram = glCreateProgram(); // najdolezitejsie
	glAttachShader(this->shaderProgram, fragmentShader);
	glAttachShader(this->shaderProgram, vertexShader);
	glLinkProgram(this->shaderProgram);

	GLint status;
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);

	testStatus(status);
}

void Shader::useProgram() {
	glUseProgram(this->shaderProgram);
}

void Shader::testStatus(GLint status) {
	
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void Shader::sendUniform(const GLchar* name, glm::mat4 M) {
	GLint uniformID = glGetUniformLocation(this->shaderProgram, name);
	if (uniformID >= 0) {
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(M)); // glm::value_ptr(M) == &M[0][0]
	}
	else {
		fprintf(stderr, "Uniform variable not found\n");
	}
}

void Shader::sendUniform(const GLchar* name, glm::vec3 V) {
	GLint uniformID = glGetUniformLocation(this->shaderProgram, name);
	if (uniformID >= 0) {
		glm::mat4 M = glm::mat4(1.0f);
		M = glm::translate(M, V);
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(M));
	}
	else {
		fprintf(stderr, "Uniform variable not found\n");
	}
}

Shader::~Shader() {
	delete this;
}