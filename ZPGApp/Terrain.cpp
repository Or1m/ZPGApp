#include "Terrain.h"

Terrain::Terrain(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath)
:	Terrain(points, countOfPoints, indexes, countOfIndexes, isWithIndexes, shaderPath, 1) { }

Terrain::Terrain(const float points[], const int countOfPoints, const unsigned int indexes[], const int countOfIndexes, bool isWithIndexes, const std::string& shaderPath, int lightCount)
:	Object(points, countOfPoints, indexes, countOfIndexes, isWithIndexes, shaderPath, NULL, false, lightCount) { }