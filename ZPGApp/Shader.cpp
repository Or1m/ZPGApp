#include "Shader.h"

//create and compile shaders
Shader::Shader(const char* vertex_shader, const char* fragment_shader) {
	this->vertex_shader = vertex_shader;
	this->fragment_shader = fragment_shader;

	this->shaderProgram = glCreateProgram(); // najdolezitejsie

	this->vertexShader = compileShader(GL_VERTEX_SHADER, this->vertex_shader);
	this->fragmentShader = compileShader(GL_FRAGMENT_SHADER, this->fragment_shader);

	glAttachShader(this->shaderProgram, this->fragmentShader);
	glAttachShader(this->shaderProgram, this->vertexShader);

	glLinkProgram(this->shaderProgram);

	GLint status;
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);

	testLinkStatus(status);
}

GLuint Shader::compileShader(GLuint type, const char* source) {
	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

	return testCompileStatus(status, shaderID, type) == 1 ? shaderID : 0;
}

void Shader::useProgram() {
	glUseProgram(this->shaderProgram);
}

GLuint Shader::testCompileStatus(GLint status, GLuint shaderID, GLuint type) {

	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1]; // (GLchar*)alloca(infoLogLength * sizeof(char));
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, strInfoLog);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << strInfoLog << std::endl;
		glDeleteShader(shaderID);
		delete[] strInfoLog;

		return 0;
	}

	return 1;
}

void Shader::testLinkStatus(GLint status) {
	
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;

		glDeleteProgram(this->shaderProgram);
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
		glUniform3f(uniformID, V.x, V.y, V.z);
	}
	else {
		fprintf(stderr, "Uniform variable not found\n");
	}
}

Shader::~Shader() {
	glDeleteShader(this->vertexShader);
	glDeleteShader(this->fragmentShader);
	glDeleteProgram(this->shaderProgram);
	delete this;
}