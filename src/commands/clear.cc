#include <clear.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <glfw3.h>

// --------------------------------------------------- //

Suffer::Clear::Clear(){
	cmd_type_ = Command::kRender;
}

// --------------------------------------------------- //

Suffer::Clear::~Clear(){

}

// --------------------------------------------------- //

void Suffer::Clear::Execute() const{
	glClearColor(color_.r, color_.g, color_.b, 1.0f);
  
  glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glDepthFunc(GL_LESS);
}

// --------------------------------------------------- //