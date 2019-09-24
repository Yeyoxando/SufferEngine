#include "window.h"
#include "glfw3.h"

Suffer::Window::Window(){

}

Suffer::Window::~Window(){

}

bool Suffer::Window::init(int width, int height){

	if(!glfwInit()){
		return false;
	}
	
	GLFWwindow* window = glfwCreateWindow(width, height, "Suffer", NULL, NULL);
	if (!window)
		return false;

	glfwMakeContextCurrent(window);

	return true;

}

bool Suffer::Window::processEvents(){
	return true;
}

void Suffer::Window::finish(){

}
