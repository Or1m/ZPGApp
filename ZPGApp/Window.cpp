#include "Window.h"

#include<iostream>

#include "Callbacks.h"
#include "Camera.h"

Window* Window::instance = NULL;

Window* Window::getInstance() {
	if (instance == NULL) {
		instance = new Window(800, 600, "ZPG");
	}

	return instance;
}

Window* Window::getInstance(int width, int height, const char* title) {
	if (instance != NULL)
		std::cout << "Warning instance is already created";
	else
		instance = new Window(width, height, title);

	return instance;
}

Window::Window(int width, int height, const char* title) 
:	width(width), height(height), title(title) {
	glfwSetErrorCallback(Callbacks::error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);

	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	int w_width, h_height;
	glfwGetFramebufferSize(this->window, &w_width, &h_height);
	float ratio = w_width / (float)h_height;
	glViewport(0, 0, w_width, h_height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Camera::getInstance()->setCenter(width, height);
}


bool Window::windowShouldNotClose() const {
	return !glfwWindowShouldClose(this->window);
}

void Window::swapBuffer() const { 
	/**
	 * Swaps the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) 
	 * that is used to render to during this render iteration and show it as output to the screen.
	 * Put the stuff we’ve been drawing onto the display
	 */
	glfwSwapBuffers(this->window);
}

void Window::pollEvents() const {
	/**
	 * Checks if any events are triggered (like keyboard input or mouse movement events), 
	 * updates the window state, and calls the corresponding functions (which we can register via callback methods).
	 */
	glfwPollEvents();
}

void Window::destroyWindow() const {
	glfwDestroyWindow(this->window);
}

void Window::terminateWindow() const {
	/**
	 * Clean/delete all of GLFW's resources that were allocated. 
	 */
	glfwTerminate();
}


void Window::attachCallbacks() const{

	// Sets the key callback
	glfwSetKeyCallback(window, Callbacks::key_callback); // stlacenie klavesy

	glfwSetCursorPosCallback(window, Callbacks::cursor_callback); // pohyb kurzora

	glfwSetWindowSizeCallback(window, Callbacks::window_size_callback); // resize okna

	glfwSetMouseButtonCallback(window, Callbacks::button_callback); // stlacenie mysky

	//glfwSetWindowFocusCallback(window, Callbacks::window_focus_callback); // focus na okno

	//glfwSetWindowIconifyCallback(window, Callbacks::window_iconify_callback); // stlacenie jednej z troch hornych ikon okna

	/*glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos)
		-> void {Window::getInstance()->cursor_callback(window, mouseXPos, mouseYPos); });*/
}