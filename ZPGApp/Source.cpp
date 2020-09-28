//Include GLFW  
#include <GLFW/glfw3.h>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	GLFWwindow* window;

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

		glfwSwapBuffers(window); // PC ma 2+ bufferov a na jedno sa pozeras, do druheho kreslis a ked dokreslis swapnu sa
								 // Aby nedochadzalo k prazdnym miestam

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}