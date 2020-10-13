#pragma once
#include "Object.h"

class Renderer {
public:
	static Renderer* getInstance();

	void draw(const Object& objectToDraw) const;
	void clear() const;

private:
	static Renderer* instance;
	Renderer();
	~Renderer();
};

