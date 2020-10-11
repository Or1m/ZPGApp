#pragma once
#include "Header.h"
#include <vector>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	bool normalized;
};

class VertexBufferLayout {
public:
	VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		elements.push_back({GL_FLOAT, count, GL_FALSE });
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
	}

private:
	std::vector<VertexBufferElement> elements;
};

