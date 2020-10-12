#pragma once

class Camera {
public:
	static Camera* getInstance();

private:
	static Camera* instance;

	Camera();
	~Camera();
};

