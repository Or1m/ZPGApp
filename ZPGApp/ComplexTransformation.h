#pragma once
#include "Transformation.h"

#include <vector>

#include "Move.h"
#include "Scale.h"

class ComplexTransformation : public Transformation {
public:
	ComplexTransformation();
	~ComplexTransformation();

	glm::mat4 add(Transformation* tr);
	void addNotApply(Transformation* tr);
	glm::mat4 apply() override;
	glm::mat4 getTransformation() { return this->modelMatrix; }

private:
	std::vector<Transformation*>* children;
};

