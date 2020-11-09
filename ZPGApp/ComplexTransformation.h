#pragma once
#include "Transformation.h"

#include <vector>

class ComplexTransformation : public Transformation {
public:
	ComplexTransformation();
	~ComplexTransformation();

	void add(Transformation* tr);
	glm::mat4 apply() override;

private:
	std::vector<Transformation*>* children;
};

