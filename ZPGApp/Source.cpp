#include "Application.h"
#include <fstream>
#include <string>
#include <sstream>

const int numOfElements = 12;

// points of triangle in Index buffer
float points[] = {
	-0.5f, -0.5f, 0.0f, // 0
	 0.5f, -0.5f, 0.0f,	// 1
	 0.5f,  0.5f, 0.0f,	// 2
	-0.5f,  0.5f, 0.0f	// 3
};

// indexes of points
unsigned int indices[] {
	0, 1, 2,
	2, 3, 0
};

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath) {
	std::ifstream stream(filePath);

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
			else if(line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

int main(void)  {

	const std::string shaderPath = "Resources/Shaders/Basic.shader";

	glm::mat4 M = glm::mat4(1.0f); 
	glm::vec3 V = glm::vec3(.0f, 1.0f, .0f);
	//M = glm::translate(M, glm::vec3(.5f, 0.5f, 0.0f));
	//M = glm::scale(M, glm::vec3(0.5f));
	//M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//std::cout << glm::to_string(M) << std::endl;
	
	
	// Variant 1
	/*Application* application = Application::getInstance();
	application->setPoints(points, sizeof(points));
	application->setShader(vertex_shader, fragment_shader);*/

	ShaderProgramSource source = ParseShader(shaderPath);

	// Variant 2
	Application* application = Application::getInstance(
		new WindowOptions(800, 600, "ZPG"), 
		new Shaders(source.vertexSource.c_str(), source.fragmentSource.c_str()),
		points, numOfElements * sizeof(float), indices
	);

	application->setTransform(M);
	application->setTransform(V);

	//application->printVersionInfo();
	//application->attachCallbacks();
	//application->testGLM();
	
	application->run();
	return 0;
}