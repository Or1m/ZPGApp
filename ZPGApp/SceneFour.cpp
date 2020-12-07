#include "SceneFour.h"

#include "Vendor/objloader.h"

void SceneFour::onLoad() {
	objects->push_back(new TexturedPlain(constantPath, texturePath, 1));

	/*std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;

	loadOBJ(domePath.c_str(), vertices, uvs, normals);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	objects->push_back(new Object(&vertices[0], sphereCount, NULL, NULL, false, phongPath, 1));*/

	lights->push_back(new Light(1));
	
	for (const auto& object : *objects) {
		object->addLight(lights->at(0));

		object->changeColor(glm::vec3(1.0, 1.0, 1.0));
		object->move(glm::vec3(0.0, -1.0, -.5));
	}

	objects->at(0)->scale(glm::vec3(20.0f, 20.0f, 20.0f));
	lights->at(0)->setDirection(glm::vec3(0.5, -1.0, 0.0));
}

void SceneFour::onUpdate() {
	for (const auto& object : *this->objects) {

		Renderer::getInstance()->draw(*object);
	}
}