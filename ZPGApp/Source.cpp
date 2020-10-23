#include "Application.h"

#include <iostream>

int main(void)  {
	int scene = 1;

	std::cout << "Select scene" << std::endl;
	std::cin >> scene;
	if (std::cin.fail()) scene = 1;

	Application::getInstance()->attachCallbacks();
	Application::getInstance()->printVersionInfo();
	Application::getInstance()->run(scene);
    
	return 0;
}