#pragma once

#include "Scene.h"

class SceneMGA : public Scene {
public:
	SceneMGA() { };
	~SceneMGA() { };

	void onLoad()   override;
	void onUpdate() override;

private:
	glm::vec3* arr;

	float t = 0.0f;
	float step = 0.01f;
};