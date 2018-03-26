#include "stdafx.h"
#include <string>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Import.h"
#include "Model.h"
#include "Shader.h"

int window_width = 640, window_height = 480;

void FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	window_width = width;
	window_height = height;
}

int main(int argc, const char * argv[])
{
	if (argc == 1) {
		std::cout << "Usage: AssimpViewer <filename> " << std::endl;
		return -1;
	}

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "AssimpViewer", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferResizeCallback);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << glewGetErrorString(err) << std::endl;
		return -1;
	}

	std::string filename = argv[1];
	std::cout << "Loading " << filename << std::endl;

	Shader* shader = new Shader();
	shader->AddComponent("shaders/fs.glsl", GL_FRAGMENT_SHADER);
	shader->AddComponent("shaders/vs.glsl", GL_VERTEX_SHADER);
	shader->Link();
	shader->Use();

	Model* m = Import::LoadFile(filename);

	while (!glfwWindowShouldClose(window))
	{
		m->Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
