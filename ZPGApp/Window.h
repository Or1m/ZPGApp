#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
	static Window* getInstance();
	static Window* getInstance(int width, int height, const char* title);

	bool windowShouldNotClose() const;

	void swapBuffer()		const;
	void pollEvents()		const;
	void destroyWindow()	const;
	void terminateWindow()	const;

	void attachCallbacks()	const;

	int getWidth()  const { return this->width;  }
	int getHeight() const { return this->height; }

private:
	static Window* instance;
	GLFWwindow* glfwWindow;

	int width;
	int height;
	const char* title;

	Window(int width, int height, const char* title);
	~Window() {}
};