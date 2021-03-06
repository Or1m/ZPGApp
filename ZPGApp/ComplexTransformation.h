#pragma once

#include "Transformation.h"
#include "Move.h"
#include "Scale.h"
#include "Rotate.h"

#include <vector>

class ComplexTransformation : public Transformation {
public:
	ComplexTransformation();
	~ComplexTransformation();

	glm::mat4 add(Transformation* tr);
	void addNotApply(Transformation* tr);

	glm::mat4 apply() override;

private:
	std::vector<Transformation*>* children;
};

