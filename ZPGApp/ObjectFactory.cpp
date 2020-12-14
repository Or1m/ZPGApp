#include "ObjectFactory.h"
#include "Vendor/objloader.h"

#include "glm/gtc/noise.hpp"

#include <iostream>

SkyBox* ObjectFactory::createSkyBox(const std::string& modelPath, const std::string& shaderPath)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	loadOBJ(modelPath.c_str(), vertices, uvs, normals);

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

	return new SkyBox(arr, count, NULL, NULL, false, shaderPath);
}

Terrain* ObjectFactory::createTerrain(int xCount, int zCount, int width, int height, float range, const std::string& shaderPath) {
	const int y = 0;

	std::vector<glm::vec3> plain_points;

	std::vector<glm::vec3> m_pos;
	std::vector<glm::vec3> m_nor;
	std::size_t m_numberOfVert;

	float step_x = (float)width / (float)xCount;
	float step_z = (float)height / (float)zCount;

	for (float i = 0; i < (float)width; i += step_x)
	{
		for (float j = 0; j < (float)height; j += step_z)
		{
			float x = i;
			float z = j;
			glm::vec3 point = glm::vec3(x, y, z);

			plain_points.emplace_back(point);
		}
	}


	for (int i = 0; i < (int)plain_points.size(); i++)
	{
		glm::vec3 vertex1 = plain_points.at(i);
		glm::vec3 vertex2 = glm::vec3(plain_points.at(i).x + step_x, plain_points.at(i).y, plain_points.at(i).z);
		glm::vec3 vertex3 = glm::vec3(plain_points.at(i).x, plain_points.at(i).y, plain_points.at(i).z + step_z);
		glm::vec3 vertex4 = glm::vec3(plain_points.at(i).x + step_x, plain_points.at(i).y, plain_points.at(i).z + step_z);

		if (vertex1.x != width - step_x && vertex1.z != height - step_z)
		{
			m_pos.emplace_back(vertex1);
			m_pos.emplace_back(vertex2);
			m_pos.emplace_back(vertex3);

			m_pos.emplace_back(vertex4);
			m_pos.emplace_back(vertex3);
			m_pos.emplace_back(vertex2);
		}
	}

	m_numberOfVert = m_pos.size();

	float max = m_pos.at(0).y;
	float min = m_pos.at(0).y;
	for (int i = 0; i < m_numberOfVert; i++)
	{
		glm::vec2 vertex_xz = glm::vec2(m_pos.at(i).x, m_pos.at(i).z);
		float new_y = range * glm::perlin(vertex_xz);

		m_pos.at(i) = glm::vec3(m_pos.at(i).x, new_y, m_pos.at(i).z);

		if (m_pos.at(i).y > max)
		{
			max = m_pos.at(i).y;
		}

		if (m_pos.at(i).y < min)
		{
			min = m_pos.at(i).y;
		}
	}

	//this->m_shader->sendUniform("max_height", range * max);

	////gen normals
	for (int i = 0; i < m_numberOfVert; i += 3)
	{
		glm::vec3 vector1 = m_pos.at(i + 1) - m_pos.at(i);
		glm::vec3 vector2 = m_pos.at(i + 2) - m_pos.at(i);
		glm::vec3 new_normal = glm::cross(vector1, vector2);

		m_nor.emplace_back(-1.0f * new_normal);
		m_nor.emplace_back(-1.0f * new_normal);
		m_nor.emplace_back(-1.0f * new_normal);
	}

	int count = m_numberOfVert;
	int size = count * 6;

	float* arr = new float[size];

	for (int i = 0, j = 0; i < size; i += 6, j += 1) {
		arr[i + 0] = m_pos[j].x;
		arr[i + 1] = m_pos[j].y;
		arr[i + 2] = m_pos[j].z;

		arr[i + 3] = m_nor[j].x;
		arr[i + 4] = m_nor[j].y;
		arr[i + 5] = m_nor[j].z;
	}

	return new Terrain(arr, count, NULL, NULL, false, shaderPath);
}


Object* ObjectFactory::internalLoadObject(const std::string& modelPath, const std::string& shaderPath, const std::string* texturePath) {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	loadOBJ(modelPath.c_str(), vertices, uvs, normals);

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

	return new Object(arr, count, NULL, NULL, false, shaderPath, texturePath, true, 1);
}