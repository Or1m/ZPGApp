#include "Application.h"

#include "Resources/Models/sphere.h"
#include "Resources/Models/suzi_flat.h"

#include <iostream>

int main(void)  {
	std::string shaderPath = "Resources/Shaders/Phong.shader";

	Application* application = Application::getInstance();
	application->createObject(shaderPath, sphere, sphereCount, NULL, NULL, false);

	//application->printVersionInfo();
	application->attachCallbacks();
	
    application->run(1);
    
	return 0;
}