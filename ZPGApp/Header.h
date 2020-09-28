#pragma once

struct WindowOptions
{
	int windowWidth; 
	int windowHeight; 
	const char* windowTitle;

	WindowOptions(int windowWidth, int windowHeight, const char* windowTitle) {
		this->windowWidth = windowWidth;
		this->windowHeight = windowHeight;
		this->windowTitle = windowTitle;
	}
};

struct Shaders
{
	const char* vertex_shader;
	const char* fragment_shader;

	Shaders() {
		vertex_shader = NULL;
		fragment_shader = NULL;
	}

	Shaders(const char* vertex_shader, const char* fragment_shader) {
		this->vertex_shader = vertex_shader;
		this->fragment_shader = fragment_shader;
	}
};