#include "Terrain.h"

Terrain::Terrain(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath)
	: Object(points, countOfPoints, indexes, countOfIndexes, isWithIndexes, shaderPath, false, 1) {
}