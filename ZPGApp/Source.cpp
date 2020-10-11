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


int main(void)  {

	std::string shaderPath = "Resources/Shaders/Basic.shader";

	glm::mat4 M = glm::mat4(1.0f); 
	glm::vec3 V = glm::vec3(1.0f, 1.0f, .0f);
	//M = glm::translate(M, glm::vec3(.5f, 0.5f, 0.0f));
	//M = glm::scale(M, glm::vec3(0.5f));
	//M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//std::cout << glm::to_string(M) << std::endl;
	

	Application* application = Application::getInstance(
		new WindowOptions(800, 600, "ZPG"), 
		shaderPath, points, numOfElements * sizeof(float), indices
	);

	application->setTransform(M);
	application->setTransform(V);

	//application->printVersionInfo();
	//application->attachCallbacks();
	//application->testGLM();
	
	application->run();
	return 0;
}