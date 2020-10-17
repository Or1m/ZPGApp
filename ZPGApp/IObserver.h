#pragma once

class IObserver {
public:
	virtual void update(glm::mat4 view) = 0;
};