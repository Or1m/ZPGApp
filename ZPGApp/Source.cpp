#include "Application.h"

const char* vertex_shader = "#version 330\n"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"uniform vec3 vec;"
"out vec4 color;"
"layout(location=0) in vec3 vp;"
"void main () {"
"color = vec4(vec, 1.0);"
" gl_Position = modelMatrix * vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"in vec4 color;"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = color;"
"}";

const int numOfElements = 9;

// points of triangle
float points[numOfElements] = { 
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

// points of rectangle
//float points[] = {
//	-0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.0f,
//	0.5f, -0.5f, 0.0f,
//	-0.5f, -0.5f, 0.0f
//};

int main(void)  {

	glm::mat4 M = glm::mat4(1.0f); 
	glm::vec3 V = glm::vec3(2.5f, .5f, 0.0f);
	M = glm::translate(M, glm::vec3(.5f, 0.5f, 0.0f));
	//M = glm::scale(M, glm::vec3(0.5f));
	//M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//std::cout << glm::to_string(M) << std::endl;
	
	
	// Variant 1
	/*Application* application = Application::getInstance();
	application->setPoints(points, sizeof(points));
	application->setShader(vertex_shader, fragment_shader);*/

	// Variant 2
	Application* application = Application::getInstance(
		new WindowOptions(800, 600, "ZPG"), 
		new Shaders(vertex_shader, fragment_shader), 
		points, numOfElements * sizeof(float)
	);

	application->setTransform(M);
	application->setTransform(V);

	//application->printVersionInfo();
	//application->attachCallbacks();
	//application->testGLM();
	
	application->run();
	return 0;
}