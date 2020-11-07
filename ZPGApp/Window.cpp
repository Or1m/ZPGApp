#include "Window.h"

#include<iostream>
#include "Camera.h"
#include "SceneManager.h"

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
	glfwSetErrorCallback(error_callback);

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


#pragma region Callbacks
void Window::attachCallbacks() const{

	// Sets the key callback
	glfwSetKeyCallback(window, key_callback); // stlacenie klavesy

	glfwSetCursorPosCallback(window, cursor_callback); // pohyb kurzora

	glfwSetWindowSizeCallback(window, window_size_callback); // resize okna

	glfwSetMouseButtonCallback(window, button_callback); // stlacenie mysky

	//glfwSetWindowFocusCallback(window, window_focus_callback); // focus na okno

	//glfwSetWindowIconifyCallback(window, window_iconify_callback); // stlacenie jednej z troch hornych ikon okna

	/*glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos)
		-> void {Window::getInstance()->cursor_callback(window, mouseXPos, mouseYPos); });*/
}

void Window::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W)
		Camera::getInstance()->toFront();
	if (key == GLFW_KEY_S)
		Camera::getInstance()->toBack();
	if (key == GLFW_KEY_A)
		Camera::getInstance()->toLeft();
	if (key == GLFW_KEY_D)
		Camera::getInstance()->toRight();
}

void Window::cursor_callback(GLFWwindow* window, double mouseX, double mouseY) {
	//printf("cursor_pos_callback %f, %f; %d, %d\n", (float)mouseX, (float)mouseY, 0, 0); // (int)clickX, (int)clickY)

	Camera::getInstance()->changeDirection((float)mouseX, (float)mouseY);
}

void Window::window_size_callback(GLFWwindow* window, int width, int height) {
	//printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}


void Window::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback \n");
}

void Window::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback \n");
}

void Window::button_callback(GLFWwindow* window, int button, int action, int mode) {
	//if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		//printf("cursor_click_callback %d, %d\n", (int)xpos, (int)ypos);


		//naètení ID a pozice ve svìtových souøadnicích
		//GLbyte color[4];
		GLfloat depth;
		GLuint index;

		GLint x = (GLint)xpos;
		GLint y = (GLint)ypos;

		int newy = (int)Window::getInstance()->height - y;

		//glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		//printf("Clicked on pixel %d, %d, color %02hhx %02hhx %02hhx %02hhx, depth %f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
	
		//std::cout << index << std::endl;

		glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::mat4 view = Camera::getInstance()->getCamera();
		glm::mat4 projection = Camera::getInstance()->getProjection();
		glm::vec4 viewPort = glm::vec4(0, 0, Window::getInstance()->width, Window::getInstance()->height);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		SceneManager::getInstance()->getScene()->setSelected(index, pos);
		printf("unProject[%f, %f, %f]\n", pos.x, pos.y, pos.z);
	}
}
#pragma endregion