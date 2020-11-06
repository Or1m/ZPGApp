#pragma once
#include <vector>

#include "Renderer.h"

#include "Object.h"
#include "Light.h"

#include "Sphere.h"
#include "SuziFlat.h"
#include "SuziSmooth.h"
#include "Plain.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	virtual void onLoad() {};
	virtual void onUpdate() {};

	void setSelected(int selected);

protected:
	std::vector<Object*>*	objects;
	std::vector<Light*>*	lights;

	int selected;

	const std::string constantPath		= "Resources/Shaders/Constant.shader";
	const std::string lambertPath		= "Resources/Shaders/Lambert.shader";
	const std::string phongPath			= "Resources/Shaders/Phong.shader";
	const std::string blinnPhongPath	= "Resources/Shaders/Blinn-Phong.shader";
};