#include "Callbacks.h"
#include "Camera.h"
#include "Window.h"
#include "SceneManager.h"

#include <iostream>

static bool pressed = false;

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
	//printf("cursor_pos_callback %f, %f; %d, %f\n", (float)mouseX, (float)mouseY, 0, 0.0); // (int)clickX, (int)clickY)

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

		float middleX = Window::getInstance()->getWidth() / 2.0f;
		float middleY = Window::getInstance()->getHeight() / 2.0f;

		if (!pressed) {
			mouseX = middleX;
			mouseY = middleY;
		}

		Camera::getInstance()->changeDirection(middleX - (float)mouseX, middleY - (float)mouseY);

		glfwSetCursorPos(window, middleX, middleY);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		pressed = true;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE && pressed) {

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		pressed = false;
	}
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
		glfwGetCursorPos(window, &xpos, &ypos);

		//na�ten� ID a pozice ve sv�tov�ch sou�adnic�ch
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

		/**
		 * Prevadza bod spat do lokalneho alebo globalneho suradnicoveho systemu
		 * @param 1 screenX
		 * @param 2 view
		 * @param 3 projection
		 * @param 4 viewPort
		 */
		glm::vec3 pos = glm::unProject(
			glm::vec3(x, newy, depth), Camera::getInstance()->getCamera(), Camera::getInstance()->getProjection(),
			glm::vec4(0, 0, Window::getInstance()->getWidth(), Window::getInstance()->getHeight())
		);  
		//printf("unProject[%f, %f, %f]\n", pos.x, pos.y, pos.z);

		SceneManager::getInstance()->getScene()->setSelected(index, pos);
	}
}


void Callbacks::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback \n");
}

void Callbacks::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback \n");
}