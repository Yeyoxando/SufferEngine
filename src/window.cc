// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#include <window.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// --------------------------------------------------------------//

struct Suffer::Window::Data {

  GLFWwindow* window_;

};

// --------------------------------------------------------------//

Suffer::Window::Window(){

  data_ = new Data();

}

// --------------------------------------------------------------//

Suffer::Window::~Window(){

  if (!data_) return;
  delete data_;
  data_ = nullptr;

}

// --------------------------------------------------------------//

bool Suffer::Window::Open(int width, int height){

	// GLFW init
	static bool window_init = false;
	if (window_init) return true;

	if(!glfwInit()){
		return false;
	}

	window_init = true;

	data_->window_ = glfwCreateWindow(width, height, "Suffer Engine", NULL, NULL);
	if (!data_->window_) return false;
	glfwMakeContextCurrent(data_->window_);

	// GLEW init
	if (glewInit() != GLEW_OK) {
		return false;
	}
	
	// ImGui init
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("../../../resources/fonts/comf_light.ttf", 13.0f);
	io.Fonts->Build();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // Substitute this by our methods
	ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

	return true;

}

// --------------------------------------------------------------//

void Suffer::Window::ProcessEvents(){

	glfwPollEvents();

}

// --------------------------------------------------------------//

void Suffer::Window::SwapBuffers(){

  glfwSwapBuffers(glfwGetCurrentContext());

}

// --------------------------------------------------------------//

void Suffer::Window::Close(){

  glfwDestroyWindow(data_->window_);
  glfwTerminate();

}