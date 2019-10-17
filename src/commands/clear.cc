#include <clear.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <glfw3.h>

// --------------------------------------------------- //

Clear::Clear(){

}

// --------------------------------------------------- //

Clear::~Clear(){

}

// --------------------------------------------------- //

void Clear::Execute(){
	glClearColor(color_.r, color_.g, color_.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

// --------------------------------------------------- //