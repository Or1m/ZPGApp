#include "Application.h"
#include "Renderer.h"

Application* Application::instance = NULL;
Application* Application::getInstance() {

	if (instance == NULL) {
		instance = new Application(800, 600, "ZPG");
	}

	return instance;
}

Application* Application::getInstance(int width, int height, const char* title) {

	if (instance != NULL)
		std::cout << "Warning instance is already created";
	else
		instance = new Application(width, height, title);

	return instance;
}

Application::Application(int width, int height, const char* title) {
	this->M = glm::mat4(1.0f);
	this->V = glm::vec3(0.5f, 0.5f, 0.5f);
	

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	int wwidth, hheight;
	glfwGetFramebufferSize(window, &wwidth, &hheight);
	float ratio = wwidth / (float)hheight;
	glViewport(0, 0, wwidth, hheight);
}

Application::~Application() {
	shader->~Shader();
	shader = NULL;

	object->~Object();
	object = NULL;

	delete instance;
	instance = NULL;
}

void Application::createObject(std::string& shaderPath, float floats[], int sizeOfPoints, unsigned int indexes[], int sizeOfIndexes) {
	this->object = new Object();

	this->object->createVBO(floats, sizeOfPoints);
	this->object->createVAO(indexes);
	
	this->shader = new Shader(shaderPath);
}

void Application::run() {
	Renderer renderer;
	float test = 0.0;

	while (!glfwWindowShouldClose(window)) {

		renderer.clear();

		//shader->useProgram();
		this->M = glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		this->V = glm::vec3(1.0f, test > 1 ? test = 0.0 : test += 0.005, 1.0);

		shader->sendUniform("modelMatrix", this->M);
		shader->sendUniform("col", this->V);

		renderer.draw(*this->object->vertexArray, *this->object->indexBuffer, *this->shader);
		
		glfwPollEvents(); // update other events like input handling
		
		glfwSwapBuffers(window); // put the stuff we’ve been drawing onto the display
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::printVersionInfo() {

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Application::testGLM() {
	
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
}

void Application::setTransform(glm::mat4 M){
	this->M = M;
}

void Application::setTransform(glm::vec3 V) {
	this->V = V;
}

#pragma region Callbacks
void Application::attachCallbacks() {

	// Sets the key callback
	glfwSetKeyCallback(window, key_callback); // stlacenie klavesy

	glfwSetMouseButtonCallback(window, button_callback); // stlacenie mysky

	glfwSetWindowFocusCallback(window, window_focus_callback); // focus na okno

	glfwSetWindowIconifyCallback(window, window_iconify_callback); // stlacenie jednej z troch hornych ikon okna

	glfwSetWindowSizeCallback(window, window_size_callback); // resize okna

	glfwSetCursorPosCallback(window, cursor_callback); // pohyb kurzora

	/*glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos)
		-> void {Application::getInstance()->cursor_callback(window, mouseXPos, mouseYPos); });*/
}


void Application::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Application::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback \n");
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double mouseX, double mouseY) {
	//printf("cursor_callback \n");
	printf("cursor_pos_callback %d, %d; %d, %d\n", (int)mouseX, (int)mouseY, 0, 0); // (int)clickX, (int)clickY)
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
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