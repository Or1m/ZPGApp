#include "Application.h"

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

	//application->printVersionInfo();
	//application->attachCallbacks();
	//application->testGLM();

	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
	
	application->run();
	return 0;
}