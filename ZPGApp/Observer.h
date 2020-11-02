#pragma once
#include <glm\ext\matrix_float4x4.hpp>

class Camera;
class Light;

class Observer {
public:
	virtual void update(Camera& camera) = 0;
	virtual void update(Light& light)	= 0;

protected:
	Observer() {};
	virtual ~Observer() {};
};