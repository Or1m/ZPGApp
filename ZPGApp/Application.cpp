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
:	window(Window::getInstance(width, height, title)), object(NULL), renderer(Renderer::getInstance()),
	deltaTime(0.0), lastFrame(0.0) {}

Application::~Application() { 
	delete this->object; 
}


void Application::createObject(std::string& shaderPath, const float floats[], int countOfPoints, unsigned int indexes[], int countOfIndexes, bool isWithIndexes) {
	this->object = new Object(floats, countOfPoints, indexes, countOfIndexes, isWithIndexes, shaderPath);
}

void Application::run() {
	this->initShaderProgram();
	
	float test = 0.0;
	glm::vec3 V;

	glm::vec3 vectors[4] = { glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, -2.0f, 0.0f) };

	while (this->window->windowShouldNotClose()) {
		this->renderer->clear();

		V = glm::vec3(1.0f, test > 1 ? test = 0.0f: test += 0.005f, 0.0f);
		this->object->sendUniformToShader("color", V);
		this->object->sendUniformToShader("lightPosition", glm::vec3(0.0f, 0.0f, 0.0f));

		this->object->sendUniformToShader("viewPosition", Camera::getInstance()->getCameraPosition());

		for (int i = 0; i < 4; i++) {
			glm::mat4 temp = glm::translate(glm::mat4(1.0f), vectors[i]);
			temp = glm::rotate(temp, (GLfloat)glfwGetTime() * -0.5f, glm::vec3(0.0f, 0.0f, 1.0f));

			this->object->sendUniformToShader("modelMatrix", temp);
			this->renderer->draw(*this->object);
		}
		
		this->window->pollEvents();
		this->window->swapBuffer(); 

		this->countDeltaTime();
	}

	this->window->destroyWindow();
	this->window->terminateWindow();
	exit(EXIT_SUCCESS);
}

void Application::countDeltaTime() {
	float currentFrame = (float)glfwGetTime();
	this->deltaTime = currentFrame - this->lastFrame;
	this->lastFrame = currentFrame;

	Camera::getInstance()->setDeltaTime(this->deltaTime);
}

void Application::initShaderProgram() const {
	ASSERT(this->object != NULL);

	this->object->useShaderProgram();

	this->object->sendUniformToShader("projectionMatrix", Camera::getInstance()->getProjection());
	this->object->sendUniformToShader("viewMatrix", Camera::getInstance()->getCamera());
	this->object->sendUniformToShader("modelMatrix", glm::mat4(1.0f));

	this->object->sendUniformToShader("lightPosition", glm::vec3(0.0f, 0.0, 0.0));
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