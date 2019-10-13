/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-13-2019
 * Interface Source
 */

#include <interface.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glfw3.h>
#include <window.h>

// --------------------------------------------------- //

Interface::Interface(){

}

// --------------------------------------------------- //

Interface::~Interface(){

}

// --------------------------------------------------- //

void Interface::Init(){

}

// --------------------------------------------------- //

void Interface::Update(){

	// New Frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	// STUFF
	static bool open = true;
	DrawMenuBar();
	DockSpace(&open);
	static bool show_demo_window = true;
	//ImGui::ShowDemoWindow(&show_demo_window);


	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	ImGui::EndFrame();

}

// --------------------------------------------------- //

void Interface::End(){

}

// --------------------------------------------------- //

void Interface::DrawMenuBar(){

	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("Close")) {}
		ImGui::EndMenu();
	}

	

	ImGui::EndMainMenuBar();

}

// --------------------------------------------------- //

void Interface::DockSpace(bool* p_open){

	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	if (opt_fullscreen){
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	//if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
	//	window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("DockSpace", p_open, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
	ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiID dockspace_id = ImGui::GetID("SufferDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
	ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags); // Add empty node
	ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

	ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
	ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
	ImGuiID dock_id_top = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.20f, NULL, &dock_main_id);
	ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.20f, NULL, &dock_main_id);
	ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

	ImGui::DockBuilderDockWindow("Hierarchy", dock_id_left);
	ImGui::DockBuilderDockWindow("Project", dock_id_bottom);
	ImGui::DockBuilderDockWindow("Console", dock_id_bottom);
	ImGui::DockBuilderDockWindow("Inspector", dock_id_right);

	Hierarchy();
	
	Project();

	Console();

	Inspector();
	


	ImGui::End();

}

// --------------------------------------------------- //

void Interface::Hierarchy(){
	ImGui::Begin("Hierarchy");
	ImGui::Text("I'm the Hierarchy!");
	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("Close")) {}
		ImGui::EndMenu();
	}
	ImGui::End();
}

// --------------------------------------------------- //

void Interface::Console(){
	ImGui::Begin("Console");
	ImGui::Text("I'm a console!");
	ImGui::End();
}

// --------------------------------------------------- //

void Interface::Inspector(){
	ImGui::Begin("Inspector");
	ImGui::Text("I'm the Inspector");
	ImGui::End();
}

// --------------------------------------------------- //

void Interface::Project(){
	ImGui::Begin("Project");
	ImGui::Text("I'm the project structure!");
	ImGui::End();
}

// --------------------------------------------------- //
