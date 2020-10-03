#include "Application.h"

// Shaders
// chybovy vypis zavisi od vyrobcu a druhu grafiky
// na MX150 sa vypise len v ktorom shaderi je chyba
// chyba shadera sa prejavuje bielou farbou objektu
const char* vertex_shader = "#version 330\n"
"uniform mat4 modelMatrix;"
"layout(location=0) in vec3 vp;"
"void main () {"
" gl_Position = modelMatrix * vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.5, 1.0, .0, 1.0);"
"}";

// points of triangle
float points[] = {
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
	M = glm::translate(M, glm::vec3(.5f, 0.0f, 0.0f));
	M =	glm::scale(M, glm::vec3(0.5f));
	//M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	
	// Variant 1
	/*Application* application = Application::getInstance();
	application->setPoints(points, sizeof(points));
	application->setShader(vertex_shader, fragment_shader);*/

	// Variant 2
	Application* application = Application::getInstance(
		new WindowOptions(800, 600, "ZPG"), 
		new Shaders(vertex_shader, fragment_shader), 
		points, sizeof(points)
	);

	application->setTransform(M);

	//application->printVersionInfo();
	//application->attachCallbacks();
	//application->testGLM();
	
	application->run();
	return 0;
}