#include "Shader.h"
#include "Camera.h"

#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"

Shader::Shader(const std::string& filePath) 
: filePath(filePath), shaderProgram(0) {
	
	ShaderProgramSource source = this->parseShader();

	this->vertexShaderSource   = source.vertexSource.c_str();
	this->fragmentShaderSource = source.fragmentSource.c_str();

	this->createShader();

	Camera::getInstance()->attach(this);
}

Shader::~Shader() {
	glDeleteShader(this->vertexShader);
	glDeleteShader(this->fragmentShader);
	glDeleteProgram(this->shaderProgram);
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

	/**
	 * @param 1 Shader object to compile
	 * @param 2 How many strings we're passing as source code
	 * @param 3 Actual source code of the shader 
	 */
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

	return testCompileStatus(status, shaderID, type) == 1 ? shaderID : 0;
}

void Shader::createShader() {

	this->shaderProgram = glCreateProgram(); // najdolezitejsie

	this->vertexShader   = compileShader(GL_VERTEX_SHADER, this->vertexShaderSource);
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


#pragma region Observer
void Shader::update(Camera& camera) {
	this->useProgram();
	this->sendUniform("viewMatrix", camera.getCamera());
	this->sendUniform("viewPosition", camera.getPosition());
}

void Shader::update(Light& light) {
	this->useProgram();

	LightType lightType = light.getType();
	std::string idxString = std::to_string(light.getIndex());
	
	this->sendUniform(("lights[" + idxString + "].color").c_str(), light.getLightColor());
	this->sendUniform(("lights[" + idxString + "].type").c_str(), (int)lightType);

	glm::vec3 attenuation;
	if (lightType == LightType::pointLight) {
		attenuation = ((PointLight&) light).getAttenuation();
		this->sendUniform(("lights[" + idxString + "].position").c_str(), ((PointLight&) light).getLightPosition());
	}
		
	else if (lightType == LightType::spotLight) {
		attenuation = ((SpotLight&)light).getAttenuation();
		this->sendUniform(("lights[" + idxString + "].position").c_str(), ((SpotLight&) light).getLightPosition());
		this->sendUniform(("lights[" + idxString + "].direction").c_str(), ((SpotLight&)light).getLightDirection());
		this->sendUniform(("lights[" + idxString + "].cutOff").c_str(), ((SpotLight&)light).getCutOff());
	}

	if(lightType == LightType::pointLight || lightType == LightType::spotLight) {
		this->sendUniform(("lights[" + idxString + "].constant").c_str(), attenuation.x);
		this->sendUniform(("lights[" + idxString + "].linear").c_str(), attenuation.y);
		this->sendUniform(("lights[" + idxString + "].quadratic").c_str(), attenuation.z);
	}
		
	if(lightType == LightType::directionalLight)
		this->sendUniform(("lights[" + idxString + "].direction").c_str(), ((DirectionalLight&) light).getLightDirection());
}


void Shader::addLight(Light* light) {
	light->attach(this);
}
#pragma endregion

#pragma region Tests
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
#pragma endregion

#pragma region SendUniforms
void Shader::sendUniform(const GLchar* name, glm::mat4 M4) const {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	if(uniformLocation != -1)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(M4)); // glm::value_ptr(M) == &M[0][0]
}

void Shader::sendUniform(const GLchar* name, glm::vec4 V4) const {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	if (uniformLocation != -1)
		glUniform4f(uniformLocation, V4.x, V4.y, V4.z, V4.w);
}

void Shader::sendUniform(const GLchar* name, glm::vec3 V3) const {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	if (uniformLocation != -1)
		glUniform3f(uniformLocation, (GLfloat)V3.x, (GLfloat)V3.y, (GLfloat)V3.z);
}

void Shader::sendUniform(const GLchar* name, GLfloat F) const {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	if (uniformLocation != -1)
		glUniform1f(uniformLocation, F);
}

void Shader::sendUniform(const GLchar* name, GLint I) const {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	if (uniformLocation != -1)
		glUniform1i(uniformLocation, I);
}

void Shader::sendUniform(const GLchar* name, GLuint U) const {
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name);

	if (uniformLocation != -1)
		glUniform1ui(uniformLocation, U);
}
#pragma endregion