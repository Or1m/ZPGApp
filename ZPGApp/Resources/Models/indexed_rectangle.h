#pragma once

const int countOfFloats = 4 * 3;
float floats[] = {
	-0.5f, -0.5f, 0.0f, // 0
	 0.5f, -0.5f, 0.0f,	// 1
	 0.5f,  0.5f, 0.0f,	// 2
	-0.5f,  0.5f, 0.0f	// 3
};

const int countOfIndexes = 6;
unsigned int indexes[]{
	0, 1, 2,
	2, 3, 0
};