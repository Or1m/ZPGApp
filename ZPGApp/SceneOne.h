#pragma once

#include "Scene.h"

class SceneOne : public Scene {
public:
	SceneOne() { };
	~SceneOne() { };

	void onLoad() override;
	void onUpdate() override;
};

