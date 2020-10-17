#include "Application.h"
#include "Resources/Models/sphere.h"

std::string shaderPath = "Resources/Shaders/Basic.shader";

// points of triangle in Index buffer
const int countOfFloats = 4 * 3;
float floats[] = {
	-0.5f, -0.5f, 0.0f, // 0
	 0.5f, -0.5f, 0.0f,	// 1
	 0.5f,  0.5f, 0.0f,	// 2
	-0.5f,  0.5f, 0.0f	// 3
};

//float floats[] = {
//	-50.0f, -50.0f, 0.0f,	// 0
//	 50.0f, -50.0f, 0.0f,	// 1
//	 50.0f,  50.0f, 0.0f,	// 2
//	-50.0f,  50.0f, 0.0f	// 3
//};

// indexes of points
const int countOfIndexes = 6;
unsigned int indexes[]{
	0, 1, 2,
	2, 3, 0
};

int main(void)  {
	//glm::mat4 M = glm::mat4(1.0f); 
	//glm::vec3 V = glm::vec3(1.0f, 1.0f, .0f);
	//M = glm::translate(M, glm::vec3(.5f, 0.5f, 0.0f));
	//M = glm::scale(M, glm::vec3(0.5f));
	//M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//std::cout << glm::to_string(M) << std::endl;

	Application* application = Application::getInstance();
	//application->createObject(shaderPath, floats, countOfFloats * sizeof(float), indexes, countOfIndexes, true);
	application->createObject(shaderPath, sphere,  2880 * 6 * sizeof(float), indexes, countOfIndexes, false);

	//application->setTransform(M);
	//application->setTransform(V);

	//application->printVersionInfo();
	//application->attachCallbacks();
	//application->testGLM();
	
	application->run();
	return 0;
}