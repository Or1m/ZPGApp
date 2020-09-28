#include "Application.h"
#include "Object.h"
#include "Shader.h"

float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

// Shaders

// chybovy vypis zavisi od vyrobcu a druhu grafiky
// na MX150 sa vypise len v ktorom shaderi je chyba
// chyba shadera sa prejavuje bielou farbou objektu
const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;" // the position variable has attribute position 0
"void main () {"
"     gl_Position = vec4 (vp, 1.0);" // see how we directly give a vec3 to vec4's constructor
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.5, 1.0, .0, 1.0);"
"}";

int main(void)  {

	Application* application = Application::getInstance();
	application->printVersionInfo();
	application->attachCallbacks();
	application->testGLM();

	application->setPoints(points);
	application->setShaders(vertex_shader, fragment_shader);
	

	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
	
	application->run();
}