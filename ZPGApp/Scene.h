#pragma once

#include <vector>

#include "Utils.h"

#include "Renderer.h"
#include "ObjectFactory.h"
#include "Object.h"

#include "Light.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	virtual void onLoad() {};
	virtual void onUpdate() {};

	void setSelected(int selected, glm::vec3 pos);
		
	static Scene* makeScene(int choice);

protected:
	std::vector<Object*>*	objects;
	std::vector<Light*>*	lights;

	int selected;
	glm::vec3 selectionPos;

	void deselect();
		
	const std::string constantPath		= "Resources/Shaders/Constant.shader";
	const std::string lambertPath		= "Resources/Shaders/Lambert.shader";
	const std::string phongPath			= "Resources/Shaders/Phong.shader";
	const std::string blinnPhongPath	= "Resources/Shaders/Blinn-Phong.shader";
	const std::string cubeMapPath		= "Resources/Shaders/Cubemap.shader";
	const std::string terraintPath		= "Resources/Shaders/Terrain.shader";

	const std::string groundTexturePath	= "Resources/Textures/floor.png";
	const std::string skyTexturePath	= "Resources/Textures/fulldome3.png";

	const std::string domePath			= "Resources/Objects/skydome.obj";
	const std::string skyBoxPath		= "Resources/Objects/skybox.obj";
};