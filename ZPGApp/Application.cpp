#include "Application.h"

Application* Application::instance = NULL;
Application* Application::getInstance() {

	if (instance == NULL) {
		instance = new Application();
	}

	return instance;
}

Application::Application() : Application::Application(800, 600, "ZPG") {}

Application::Application(int windowWidth, int windowHeight, const char* windowTitle) {

	fragment_shader = NULL;
	vertex_shader = NULL;
	points = NULL;
	shader = NULL;
	sizeOfPoints = NULL;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	object = new Object();
}

Application::~Application() {
	shader->~Shader();
	shader = NULL;

	object->~Object();
	object = NULL;

	delete instance;
	instance = NULL;
}

void Application::run() {

	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->useProgram(); //glUseProgram(shaderProgram);
		object->bindVertexArray(); //glBindVertexArray(VAO);

		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we�ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::printVersionInfo() {

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Application::attachCallbacks() {

	// Sets the key callback
	glfwSetKeyCallback(window, key_callback); // stlacenie klavesy

	glfwSetCursorPosCallback(window, cursor_callback); // pohyb kurzora

	glfwSetMouseButtonCallback(window, button_callback); // stlacenie mysky

	glfwSetWindowFocusCallback(window, window_focus_callback); // focus na okno

	glfwSetWindowIconifyCallback(window, window_iconify_callback); // stlacenie jednej z troch hornych ikon okna

	glfwSetWindowSizeCallback(window, window_size_callback); // resize okna
}

void Application::testGLM() {
	
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
}

void Application::setShaders(const char* vertex_shader, const char* fragment_shader) {
	setVertexShader(vertex_shader);
	setFragmentShader(fragment_shader);

	shader = new Shader(this->vertex_shader, this->fragment_shader);
}

void Application::setVertexShader(const char* vertex_shader) {
	this->vertex_shader = vertex_shader;
}

void Application::setFragmentShader(const char* fragment_shader) {
	this->fragment_shader = fragment_shader;
}

void Application::setPoints(float points[], int sizeOfPoints) {
	this->points = points;
	this->sizeOfPoints = sizeOfPoints;

	object->createVBO(this->points, this->sizeOfPoints);
	object->createVAO();
}

// Declaration of callback functions
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

void Application::cursor_callback(GLFWwindow* window, double x, double y) {
	printf("cursor_callback \n");
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}