#pragma once

#include "Scene.h"

class SceneTwo : public Scene {
public:
	SceneTwo();
	~SceneTwo();

	void onLoad() override;
	void onUpdate() override;

private:
	glm::vec3* vectors;
};

