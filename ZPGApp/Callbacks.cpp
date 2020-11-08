#include "Callbacks.h"

#include <iostream>

#include "Camera.h"
#include "Window.h"
#include "SceneManager.h"

//float x = 0;
//float y = 0;
//bool pressed = false;
void Callbacks::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void Callbacks::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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

void Callbacks::cursor_callback(GLFWwindow* window, double mouseX, double mouseY) {
	printf("cursor_pos_callback %f, %f; %d, %f\n", (float)mouseX, (float)mouseY, 0, 0); // (int)clickX, (int)clickY)

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		Camera::getInstance()->changeDirection(/*x + */(float)mouseX,/* y + */(float)mouseY);

		//pressed = true;
	}


	/*if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE && pressed) {
		x += mouseX;
		y += mouseY;
		pressed = false;
	}*/
}

void Callbacks::window_size_callback(GLFWwindow* window, int width, int height) {
	//printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Callbacks::button_callback(GLFWwindow* window, int button, int action, int mode) {
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

		int newy = (int)Window::getInstance()->getHeight() - y;

		//glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		//printf("Clicked on pixel %d, %d, color %02hhx %02hhx %02hhx %02hhx, depth %f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

		//std::cout << index << std::endl;

		glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::mat4 view = Camera::getInstance()->getCamera();
		glm::mat4 projection = Camera::getInstance()->getProjection();
		glm::vec4 viewPort = glm::vec4(0, 0, Window::getInstance()->getWidth(), Window::getInstance()->getHeight());
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		SceneManager::getInstance()->getScene()->setSelected(index, pos);
		//printf("unProject[%f, %f, %f]\n", pos.x, pos.y, pos.z);
	}
}


void Callbacks::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback \n");
}

void Callbacks::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback \n");
}