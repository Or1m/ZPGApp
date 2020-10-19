#include "Application.h"
#include "Resources/Models/sphere.h"

int main(void)  {
	std::string shaderPath = "Resources/Shaders/Basic.shader";

	Application* application = Application::getInstance();
	application->createObject(shaderPath, sphere, 2880, NULL, NULL, false);

	//application->printVersionInfo();
	application->attachCallbacks();
	
	application->run();
	return 0;
}
