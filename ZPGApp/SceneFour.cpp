#include "SceneFour.h"
#include "Vendor/objloader.h"

#include "Texture.h"

void SceneFour::onLoad() {
	objects->push_back(new TexturedPlain(constantPath, groundTexturePath, 1));
	//objects->push_back(new Plain(constantPath));


	
	/*this->shader->sendUniform("myTexture", this->id - 1);
	this->shader->sendUniform("hasTexture", 1);*/

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	loadOBJ(domePath.c_str(), vertices, uvs, normals);

	int count = vertices.size();
	int size = count * 8;

	float* arr = new float[size];

	for (int i = 0, j = 0; i < size; i += 8, j += 1) {
		arr[i + 0] = vertices[j].x;
		arr[i + 1] = vertices[j].y;
		arr[i + 2] = vertices[j].z;

		arr[i + 3] = normals[j].x;
		arr[i + 4] = normals[j].y;
		arr[i + 5] = normals[j].z;

		arr[i + 6] = uvs[j].x;
		arr[i + 7] = uvs[j].y;
	}

	//Object(arr, count, NULL, NULL, false, shaderPath, texturePath);

	//objects->push_back(new Object(constantPath, texturePath, domePath));
	objects->push_back(new Object(arr, count, NULL, NULL, false, constantPath, skyTexturePath));

	lights->push_back(new Light(1));
	
	int i = 0;
	for (const auto& object : *objects) {
		object->addLight(lights->at(0));


		object->changeColor(glm::vec3(1.0, 1.0, 1.0));
	}

	Texture* texture = new Texture(groundTexturePath);
	texture->bind(0);
	
	objects->at(0)->sendUniformToShader("myTexture", 0);
	objects->at(0)->sendUniformToShader("hasTexture", 1);

	Texture* texture2 = new Texture(skyTexturePath);
	texture2->bind(1);

	objects->at(1)->sendUniformToShader("myTexture", 1);
	objects->at(1)->sendUniformToShader("hasTexture", 1);


	objects->at(0)->move(glm::vec3(0.0, -1.0, -.5));
	objects->at(1)->move(glm::vec3(0.0, 0.0, 0.0));
	//objects->at(0)->scale(glm::vec3(20.0f, 20.0f, 20.0f));
	lights->at(0)->setDirection(glm::vec3(0.5, -1.0, 0.0));
}

void SceneFour::onUpdate() {

	for (const auto& object : *this->objects) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 1);
		Renderer::getInstance()->draw(*object);
	}
}