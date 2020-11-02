#include "Subject.h"

Subject::Subject()
	: observers(new std::vector<Observer*>()) {}

Subject::~Subject() {
	for (int i = 0; i < this->observers->size(); i++)
		delete this->observers->at(i);

	delete this->observers;
}


void Subject::attach(Observer* observer) {
	this->observers->push_back(observer);
}

void Subject::detach(Observer* observer) {
	auto iterator = std::find(observers->begin(), observers->end(), observer);

	if (iterator != observers->end())
		observers->erase(iterator);
}

void Subject::notify(Camera& camera) {
	for (Observer* observer : *observers)
		observer->update(camera);
}

void Subject::notify(Light& light) {
	for (Observer* observer : *observers)
		observer->update(light);
}