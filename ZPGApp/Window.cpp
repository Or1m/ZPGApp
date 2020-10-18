#include "Window.h"

#include<iostream>
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

Window::Window(int width, int height, const char* title) {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	int w_width, h_height;
	glfwGetFramebufferSize(window, &w_width, &h_height);
	float ratio = w_width / (float)h_height;
	glViewport(0, 0, w_width, h_height);

	glEnable(GL_DEPTH_TEST);
}

bool Window::windowShouldNotClose() const {
	return !glfwWindowShouldClose(this->window);
}

void Window::swapBuffer() const { 
	glfwSwapBuffers(this->window); // put the stuff we’ve been drawing onto the display
}

void Window::pollEvents() const {
	glfwPollEvents(); // update other events like input handling
}

void Window::destroyWindow() const {
	glfwDestroyWindow(this->window);
}

void Window::terminateWindow() const {
	glfwTerminate();
}

#pragma region Callbacks
void Window::attachCallbacks() const{

	// Sets the key callback
	glfwSetKeyCallback(window, key_callback); // stlacenie klavesy

	//glfwSetMouseButtonCallback(window, button_callback); // stlacenie mysky

	//glfwSetWindowFocusCallback(window, window_focus_callback); // focus na okno

	//glfwSetWindowIconifyCallback(window, window_iconify_callback); // stlacenie jednej z troch hornych ikon okna

	//glfwSetWindowSizeCallback(window, window_size_callback); // resize okna

	glfwSetCursorPosCallback(window, cursor_callback); // pohyb kurzora

	/*glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos)
		-> void {Window::getInstance()->cursor_callback(window, mouseXPos, mouseYPos); });*/
}

void Window::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	if (key == GLFW_KEY_W)
		Camera::getInstance()->toFront();
	if (key == GLFW_KEY_S)
		Camera::getInstance()->toBack();
	if (key == GLFW_KEY_A)
		Camera::getInstance()->toLeft();
	if (key == GLFW_KEY_D)
		Camera::getInstance()->toRight();

}

void Window::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback \n");
}

void Window::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback \n");
}

void Window::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Window::cursor_callback(GLFWwindow* window, double mouseX, double mouseY) {
	//printf("cursor_callback \n");
	printf("cursor_pos_callback %d, %d; %d, %d\n", (int)mouseX, (int)mouseY, 0, 0); // (int)clickX, (int)clickY)

	Camera::getInstance()->changeDirection((int)mouseX, (int)mouseY);
}

void Window::button_callback(GLFWwindow* window, int button, int action, int mode) {
	//if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		printf("cursor_click_callback %d, %d\n", (int)xpos, (int)ypos);
	}
}
#pragma endregion