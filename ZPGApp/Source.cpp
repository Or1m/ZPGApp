#include "Application.h"
#include "Resources/Models/sphere.h"
#include "Resources/Models/suzi_flat.h"

int main(void)  {
	std::string shaderPath = "Resources/Shaders/Basic.shader";

	Application* application = Application::getInstance();
	application->createObject(shaderPath, suziFlat, suziFlatCount, NULL, NULL, false);

	//application->printVersionInfo();
	application->attachCallbacks();
	
	application->run();
	return 0;
}
