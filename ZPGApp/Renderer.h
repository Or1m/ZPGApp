#pragma once
#include "Header.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Object.h"

class Renderer {
public:
	void draw(Object* objectToDraw) const;
	void clear() const;
};

