//Include GLFW  
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

//GLM test

// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);


int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Sets the key callback
	glfwSetKeyCallback(window, key_callback); // stlacenie klavesy

	glfwSetCursorPosCallback(window, cursor_callback); // pohyb kurzora

	glfwSetMouseButtonCallback(window, button_callback); // stlacenie mysky

	glfwSetWindowFocusCallback(window, window_focus_callback); // focus na okno

	glfwSetWindowIconifyCallback(window, window_iconify_callback); // stlacenie jednej z troch hornych ikon okna

	glfwSetWindowSizeCallback(window, window_size_callback); // resize okna

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f); // -50f zmeni smer rotacie

		// zaciatok veci z opengl 1.0 pre fixny retazec, tu sa o vsetko staral procak, hovoril jej co ma robit, grafika bola hlupa, dnes uz to neplati
		glBegin(GL_QUADS);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.6f, .0f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.6f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.6f, 0.6f, 0.f);
		glColor3f(1.f, 1.f, 0.f);
		glVertex3f(-0.6f, 0.6f, .0f);
		glEnd();

		/*glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-1.0f, -1.0f, .0f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(1.0f, -1.0f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(1.0f, 1.0f, 0.f);
		glEnd();
		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-1.0f, -1.0f, .0f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(-1.0f, 1.0f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(1.0f, 1.0f, 0.f);
		glEnd();*/

		/*glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-.6f, -.6f, .0f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(.6f, -.6f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(.6f, .6f, 0.f);
		glEnd();*/

		glfwSwapBuffers(window); // PC ma 2+ bufferov a na jedno sa pozeras, do druheho kreslis a ked dokreslis swapnu sa
								 // Aby nedochadzalo k prazdnym miestam

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}