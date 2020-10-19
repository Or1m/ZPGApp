#pragma once
#include <glm\ext\matrix_float4x4.hpp>

class IObserver {
public:
	virtual void update(glm::mat4 view, glm::vec3 position) = 0;
};