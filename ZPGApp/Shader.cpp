#include "Shader.h"

Shader::Shader(const std::string& filePath) {
	this->filePath = filePath;
	this->shaderProgram = 0;
	
	ShaderProgramSource source = this->parseShader();
	this->vertexShaderSource = source.vertexSource.c_str();
	this->fragmentShaderSource = source.fragmentSource.c_str();
	this->createShader();
}

Shader::~Shader() {
	glDeleteShader(this->vertexShader);
	glDeleteShader(this->fragmentShader);
	glDeleteProgram(this->shaderProgram);
	delete this;
}

#pragma warning(push)
#pragma warning(disable:6385)
ShaderProgramSource Shader::parseShader() {
	std::ifstream stream(this->filePath);

	enum class ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}
#pragma warning(pop)

GLuint Shader::compileShader(GLuint type, const char* source) {
	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

	return testCompileStatus(status, shaderID, type) == 1 ? shaderID : 0;
}

void Shader::createShader() {

	this->shaderProgram = glCreateProgram(); // najdolezitejsie

	this->vertexShader = compileShader(GL_VERTEX_SHADER, this->vertexShaderSource);
	this->fragmentShader = compileShader(GL_FRAGMENT_SHADER, this->fragmentShaderSource);

	glAttachShader(this->shaderProgram, this->fragmentShader);
	glAttachShader(this->shaderProgram, this->vertexShader);

	glLinkProgram(this->shaderProgram);

	GLint status;
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);

	testLinkStatus(status);
}

void Shader::useProgram() const {
	glUseProgram(this->shaderProgram);
}

void Shader::unbindProgram() const {
	glUseProgram(0);
}

// Shader tests
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
		std::cout << "Linker failure due to " << strInfoLog << "\n"; // fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;

		glDeleteProgram(this->shaderProgram);
	}
}

#pragma region SendUniforms
void Shader::sendUniform(const GLchar* name, glm::mat4 M4) {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	ASSERT(uniformLocation != -1);

	GLCall(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(M4))); // glm::value_ptr(M) == &M[0][0]
}

void Shader::sendUniform(const GLchar* name, glm::vec4 V4) {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	ASSERT(uniformLocation != -1);

	GLCall(glUniform4f(uniformLocation, V4.x, V4.y, V4.z, V4.w));
}

void Shader::sendUniform(const GLchar* name, glm::vec3 V3) {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	ASSERT(uniformLocation != -1);

	GLCall(glUniform3f(uniformLocation, V3.x, V3.y, V3.z));
}

void Shader::sendUniform(const GLchar* name, GLfloat F) {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	ASSERT(uniformLocation != -1);

	GLCall(glUniform1f(uniformLocation, F));
}

void Shader::sendUniform(const GLchar* name, GLint I) {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	ASSERT(uniformLocation != -1);

	GLCall(glUniform1i(uniformLocation, I));
}

void Shader::sendUniform(const GLchar* name, GLuint U) {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	ASSERT(uniformLocation != -1);

	GLCall(glUniform1ui(uniformLocation, U));
}
#pragma endregion