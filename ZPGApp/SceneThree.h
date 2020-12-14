#pragma once

#include "Scene.h"

class SceneThree : public Scene {
public:
	SceneThree() { }
	~SceneThree() { }

	void onLoad() override;
	void onUpdate() override;
};

