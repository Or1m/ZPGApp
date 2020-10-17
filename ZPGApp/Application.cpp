#include "Application.h"

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
: window(Window::getInstance(width, height, title)), object(NULL), renderer(Renderer::getInstance()) {

	this->M = glm::mat4(1.0f);
	this->V = glm::vec3(0.5f, 0.5f, 0.5f);
}

Application::~Application() {

	object->~Object();
	object = NULL;

	delete instance;
	instance = NULL;
}

void Application::createObject(std::string& shaderPath, float floats[], int sizeOfPoints, unsigned int indexes[], int countOfIndexes, bool isWithIndexes) {
	this->object = new Object(floats, sizeOfPoints, indexes, countOfIndexes, isWithIndexes, shaderPath);
}

void Application::run()  { //const ked tam nebude to priradenie?
	this->initShaderProgram();

	float test = 0.0;
	glEnable(GL_DEPTH_TEST);

	//glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
	//glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	//Projection matrix :
	//45° Field of View, 4:3 ratio, display range : 0.1 unit < 100 units
	//glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	//this->object->sendUniformToShader("projectionMatrix", projection);
	

	//glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(100, 100, 0));
	glm::mat4 view = glm::lookAt(	glm::vec3(0.0f, 0.0f, -5.0f),
									glm::vec3(0.0f, 0.0f, 0.0f),
									glm::vec3(0.0f, 1.0f, 0.0f));

	//this->eye, this->eye + this->target, this->up

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	this->object->sendUniformToShader("projectionMatrix", projection);
	this->object->sendUniformToShader("viewMatrix", view);
	this->object->sendUniformToShader("modelMatrix", glm::mat4(1.0f));

	float dis = -100.0f;

	while (this->window->windowShouldNotClose()) {
		this->M = glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime() * 0.5f, glm::vec3(0.0f, 0.0f, 1.0f));
		this->V = glm::vec3(0.0f, test > 1 ? test = 0.0f: test += 0.005f, 1.0f);

		this->renderer->clear();

		/*glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, dis += 0.5f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));

		this->object->sendUniformToShader("viewMatrix", view);*/


		//this->object->sendUniformToShader("modelMatrix", this->M);
		//this->object->sendUniformToShader("viewMatrix", view);
		this->object->sendUniformToShader("col", this->V);

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

void Application::testGLM() const {
	
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

void Application::attachCallbacks() const {
	this->window->attachCallbacks();
}