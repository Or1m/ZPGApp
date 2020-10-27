#pragma once
#include <glm\ext\matrix_float4x4.hpp>

class Camera;

class IObserver {
public:
	virtual void update(Camera& camera) = 0;
	// TODO light
};