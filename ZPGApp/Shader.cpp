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

	shaderProgram = glCreateProgram(); // najdolezitejsie
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

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