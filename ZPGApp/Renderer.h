#pragma once
#include "Object.h"

class Renderer {
public:
	void draw(Object* objectToDraw) const;
	void clear() const;
};

