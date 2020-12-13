#include "Light.h"

static int identificator = 0;

Light::Light(LightType type)
:	lightColor(glm::vec3(1.0, 1.0, 1.0)), index(identificator++), ambient(glm::vec3(0.15f, 0.15f, 0.15f)), diffuse(glm::vec3(1.0f, 1.0f, 1.0f)), 
	specular(glm::vec3(1.0f, 1.0f, 1.0f)), type(type) { }