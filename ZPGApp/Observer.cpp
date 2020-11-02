#include "Observer.h"
#include <iostream>

void Observer::update(Camera& camera) {
	std::cout << "Camera update to overeide";
}

void Observer::update(Light& light) {
	std::cout << "Light update to overeide";
}