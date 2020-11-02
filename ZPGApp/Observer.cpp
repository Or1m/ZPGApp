#include "Observer.h"
#include <iostream>

void Observer::update(Camera& camera) {
	std::cout << "Camera update";
}

void Observer::update(Light& light) {
	std::cout << "Light update";
}