#pragma once

#include "Scene.h"

class SceneFour : public Scene {
public:
	SceneFour() { };
	~SceneFour() { };

	void onLoad() override;
	void onUpdate() override;

private:
	glm::vec3* arr;

	float t = 0.0f;
	float step = 0.01f;
};