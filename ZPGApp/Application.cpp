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
	this->object = NULL;

	this->M = glm::mat4(1.0f);
	this->V = glm::vec3(0.5f, 0.5f, 0.5f);

	this->window = Window::getInstance(width, height, title);
}

Application::~Application() {

	object->~Object();
	object = NULL;

	delete instance;
	instance = NULL;
}

void Application::createObject(std::string& shaderPath, float floats[], int sizeOfPoints, unsigned int indexes[], int countOfIndexes) {
	this->object = new Object(floats, sizeOfPoints, indexes, countOfIndexes, shaderPath);
}

void Application::run() {
	Renderer renderer;
	float test = 0.0;

	while (this->window->windowShouldNotClose()) {

		renderer.clear();

		//shader->useProgram();
		this->M = glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		this->V = glm::vec3(1.0f, test > 1 ? test = 0.0 : test += 0.005, 1.0);

		this->object->sendUniformToShader("modelMatrix", this->M);
		this->object->sendUniformToShader("col", this->V);

		renderer.draw(this->object);
		
		glfwPollEvents(); // update other events like input handling
		
		this->window->swapBuffer();//glfwSwapBuffers(window); // put the stuff we’ve been drawing onto the display
	}

	this->window->destroyWindow(); //glfwDestroyWindow(window);
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

void Application::attachCallbacks() {
	this->window->attachCallbacks();
}