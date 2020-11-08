#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
	static Window* getInstance();
	static Window* getInstance(int width, int height, const char* title);

	bool windowShouldNotClose() const;
	void swapBuffer() const;
	void pollEvents() const;
	void destroyWindow() const;
	void terminateWindow() const;

	void attachCallbacks() const;

	int getWidth() const { return this->width; }
	int getHeight() const { return this->height; }

private:
	static Window* instance;
	GLFWwindow* window;

	int width;
	int height;
	const char* title;

	Window(int width, int height, const char* title);
	~Window() {}

	/*static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);*/
};

