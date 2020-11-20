#include "ComplexTransformation.h"

ComplexTransformation::ComplexTransformation()
:	children(new std::vector<Transformation*>()) {}

ComplexTransformation::~ComplexTransformation()
{
	for (unsigned int i = 0; i < this->children->size(); i++)
		delete this->children->at(i);

	delete this->children;
}


glm::mat4 ComplexTransformation::add(Transformation* tr) {
	this->children->push_back(tr);

	this->modelMatrix *= tr->apply();

	return this->modelMatrix;
}

void ComplexTransformation::addNotApply(Transformation* tr) {
	this->children->push_back(tr);
}

glm::mat4 ComplexTransformation::apply() {
	glm::mat4 temp = glm::mat4(1.0);

	for (unsigned int i = 0; i < this->children->size(); i++) {
		temp *= this->children->at(i)->apply();
	}

	return this->modelMatrix * temp;
}
