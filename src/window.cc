#include <window.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

Suffer::Window::Window(){

}

//TODO: Research
Suffer::Window::~Window(){
	glfwTerminate();
}

bool Suffer::Window::init(int width, int height){
	// GLFW init
	static bool window_init = false;
	if (window_init) return true;
	if(!glfwInit()){
		return false;
	}
	window_init = true;

	//TODO: Research
	GLFWwindow* window = glfwCreateWindow(width, height, "Suffer", NULL, NULL);
	if (!window) return false;
	glfwMakeContextCurrent(window);
	

	// GLEW init

	if (glewInit() != GLEW_OK) {
		return false;
	}
	
	// ImGui init
	ImGui::CreateContext();
	ImGuiIO io = ImGui::GetIO(); /*(void)io;*/

	io.Fonts->AddFontDefault();
	io.Fonts->Build();
	ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

	return true;

}

bool Suffer::Window::processEvents(){
	glfwPollEvents();
	return true;
}

void Suffer::Window::swapBuffers(){
	glfwSwapBuffers(glfwGetCurrentContext());
}

void Suffer::Window::finish(){

}
