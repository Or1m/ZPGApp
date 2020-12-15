#pragma once

const int rectangleCount = 4;

// normals are undefined
const float rectangle[] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, // 0
	 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, // 1
	 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, // 2
	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f  // 3
};

const int rectangleIndexCount = 6;

const unsigned int rectangleIndex[] = {
	0, 1, 2,
	2, 3, 0
};