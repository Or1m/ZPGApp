#pragma once

#include "Observer.h"
#include <vector>

class Subject {
public:
	void attach(Observer* observer);
	void detach(Observer* observer);
	void notify(Camera& camera);
	void notify(Light& light);

protected:
	std::vector<Observer*>* observers;

	Subject();
	virtual ~Subject();
};