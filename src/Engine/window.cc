// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#include <window.h>
#include <GL/glew.h>
#include <glfw3.h>
#include "common_definitions.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "internal_window.h"
#include "IconsFontAwesome5Pro.h"

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

	data_->window_ = glfwCreateWindow(width, height, "Suffer Engine", glfwGetPrimaryMonitor(), NULL);

  data_->width_ = width;
  data_->height_ = height;

	if (!data_->window_) return false;
	glfwMakeContextCurrent(data_->window_);

	// GLEW init
	if (glewInit() != GLEW_OK) {
		return false;
	}
	
	// ImGui init
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();

  static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
  ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;

	io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS, 16.0f, &icons_config, icons_ranges);
	
	io.Fonts->Build();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // TODO: Substitute this by our methods
	ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

  glfwSetCursorPos(glfwGetCurrentContext(), data_->width_ * 0.5f, data_->height_ * 0.5f);

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

// --------------------------------------------------------------//
