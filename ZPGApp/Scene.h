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
	const std::string pannaTexPath		= "Resources/Textures/panna.png";
	const std::string enviroTexPath		= "Resources/Textures/enviro.png";
	const std::string setTexPath		= "Resources/Textures/set.png";
	const std::string bookshelfTexPath	= "Resources/Textures/bookshelf.png";
	const std::string livingfTexPath	= "Resources/Textures/living.png";
	const std::string barrelTexPath		= "Resources/Textures/barrel.png";
	const std::string stolickyTexPath	= "Resources/Textures/stolickas.png";
	const std::string wellTexPath		= "Resources/Textures/well.png";
	const std::string plateTexPath		= "Resources/Textures/plate.png";
	const std::string coffeeTexPath		= "Resources/Textures/coffeee.png";
	const std::string cofTexPath		= "Resources/Textures/cof.png";
	const std::string grassTexPath		= "Resources/Textures/grass.png";
	const std::string studnaTexPath		= "Resources/Textures/studna.png";
	const std::string donutTexPath		= "Resources/Textures/donut.png";

	const std::string domePath			= "Resources/Objects/skydome.obj";
	const std::string skyBoxPath		= "Resources/Objects/skybox.obj";
	const std::string pannaPath			= "Resources/Objects/panna.obj";
	const std::string enviroPath		= "Resources/Objects/enviroment.obj";
	const std::string setPath			= "Resources/Objects/set.obj";
	const std::string bookshelfPath		= "Resources/Objects/bookshelf.obj";
	const std::string livingfPath		= "Resources/Objects/living2.obj";
	const std::string barrelPath		= "Resources/Objects/barrel.obj";
	const std::string stolickyPath		= "Resources/Objects/stolickas.obj";
	const std::string wellPath			= "Resources/Objects/well.obj";
	const std::string platePath			= "Resources/Objects/plate.obj";
	const std::string coffeePath		= "Resources/Objects/coffeee.obj";
	const std::string cofPath			= "Resources/Objects/cof.obj";
	const std::string grassPath			= "Resources/Objects/grass.obj";
	const std::string studnaPath		= "Resources/Objects/studna.obj";
	const std::string donutPath			= "Resources/Objects/donutik.obj";
	const std::string bigDonutPath		= "Resources/Objects/donut.obj";
};