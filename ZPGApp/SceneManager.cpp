#include "SceneManager.h"

#include "Renderer.h"
#include "Application.h"
#include "Camera.h"
#include "Window.h"


SceneManager* SceneManager::instance = NULL;

SceneManager* SceneManager::getInstance() {
	if (instance == NULL) {
		instance = new SceneManager();
	}

	return instance;
}

SceneManager::SceneManager() 
:	currentScene(nullptr) {}

SceneManager::~SceneManager() {
	delete this->currentScene;
}


void SceneManager::setScene(Scene& scene) {
	this->currentScene = &scene;
	this->currentScene->onLoad();
}

void SceneManager::runScene() {

	while(Window::getInstance()->windowShouldNotClose()) {
		Renderer::getInstance()->clear();

		// TODO Zapracovat deltaTime
		this->currentScene->onUpdate();

		Window::getInstance()->pollEvents();
		Window::getInstance()->swapBuffer();

		Application::getInstance()->countDeltaTime();
	}

	Window::getInstance()->destroyWindow();
	Window::getInstance()->terminateWindow();
	exit(EXIT_SUCCESS);
}