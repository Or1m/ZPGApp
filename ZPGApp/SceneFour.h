#pragma once

#include "Scene.h"

class SceneFour : public Scene {
public:
	SceneFour() { };
	~SceneFour() { };

	void onLoad() override;
	void onUpdate() override;
};