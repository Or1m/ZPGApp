#include "Application.h"
#include "Camera.h"

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

Application::Application(int width, int height, const char* title) 
: window(Window::getInstance(width, height, title)), object(NULL), renderer(Renderer::getInstance()) {}

Application::~Application() { 
	delete this->object; 
}

void Application::createObject(std::string& shaderPath, const float floats[], int countOfPoints, unsigned int indexes[], int countOfIndexes, bool isWithIndexes) {
	this->object = new Object(floats, countOfPoints, indexes, countOfIndexes, isWithIndexes, shaderPath);
}

void Application::run() const {
	this->initShaderProgram();
	glEnable(GL_DEPTH_TEST);

	float test = 0.0;
	glm::mat4 M;
	glm::vec3 V;

	
	this->object->sendUniformToShader("projectionMatrix", Camera::getInstance()->getProjection());
	this->object->sendUniformToShader("viewMatrix", Camera::getInstance()->getCamera());
	this->object->sendUniformToShader("modelMatrix", glm::mat4(1.0f));


	while (this->window->windowShouldNotClose()) {
		M = glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime() * 0.5f, glm::vec3(0.0f, 0.0f, 1.0f));
		V = glm::vec3(0.0f, test > 1 ? test = 0.0f: test += 0.005f, 1.0f);

		this->renderer->clear();

		Camera::getInstance()->toBack();


		//this->object->sendUniformToShader("modelMatrix", this->M);
		//this->object->sendUniformToShader("viewMatrix", view);
		this->object->sendUniformToShader("col", V);

		this->renderer->draw(*this->object);
		
		/*this->object->sendUniformToShader("viewMatrix", glm::translate(glm::mat4(1.0), glm::vec3(400, 300, 0)));
		this->object->sendUniformToShader("modelMatrix", glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime() * -0.5f, glm::vec3(0.0f, 0.0f, 1.0f)));
		this->object->sendUniformToShader("col", glm::vec3(1.0f, 0.0f, test > 1 ? test = 0.0f : test += 0.005f));

		this->renderer->draw(*this->object);*/

		
		this->window->pollEvents();
		this->window->swapBuffer(); 
	}

	this->window->destroyWindow();
	this->window->terminateWindow();
	exit(EXIT_SUCCESS);
}

void Application::initShaderProgram() const {
	ASSERT(this->object != NULL);

	this->object->useShaderProgram();
}

void Application::printVersionInfo() const {

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Application::attachCallbacks() const {
	this->window->attachCallbacks();
}