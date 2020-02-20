/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-13-2019
 * Interface Source
 */

#include "internal_resource_manager.h"
#include <imgui.h>
#include <scene.h>
#include <glfw3.h>
#include <input.h>
#include <stb_image.h>
#include <interface.h>
#include <display_list.h>
#include <suffermanager.h>
#include <audio_commands.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <common_definitions.h>
#include "internal_interface.h"
#include <string>

ExampleAppLog Suffer::Interface::log;

// --------------------------------------------------- //

struct Suffer::Interface::Data {

	bool LoadTextureFromFile(const char* filename, GLuint * out_texture, int* out_width, int* out_height);

};

bool Suffer::Interface::Data::LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height){
	
	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload pixels into texture
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;

}

// --------------------------------------------------- //

Suffer::Interface::Interface(){

	// Init attributes
	options_window_ = false;
	style_ = kInterfaceStyle_Red;



	is_log_opened_ = true;
	is_hierarchy_opened_ = true;
	is_inspector_opened_ = true;
	is_game_window_opened_ = true;
	is_project_window_opened_ = true;
	is_audio_window_opened_ = true;

	_ptr = new Data();

}
// --------------------------------------------------- //

Suffer::Interface::~Interface(){

	if (_ptr == nullptr) return;
	delete _ptr;


}

// --------------------------------------------------- //

void Suffer::Interface::Init(){

#ifdef DEBUG

	log.AddLog("\nGraphics Information");
	log.AddLog("\n\t[" _debug_ "] Vendor: [%s]", glGetString(GL_VENDOR));
	log.AddLog("\n\t[" _debug_ "] Renderer: [%s]", glGetString(GL_RENDERER));
	log.AddLog("\n\t[" _debug_ "] Version: [%s]\n", glGetString(GL_VERSION));

#endif

	ChangeEditorStyle();
	style_ = kInterfaceStyle_RayTeak;
	ChangeEditorStyle();

}

// --------------------------------------------------- //

void  Suffer::Interface::Update(){

	// New Frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	// STUFF
	static bool open = true;
	DrawMenuBar();
	CreateDock(&open);
	OpenWindows();
	//ImGui::ShowDemoWindow(&open);
	//ImGui::ShowMetricsWindow(&open);

}

void  Suffer::Interface::Render(){

	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	ImGui::EndFrame();

}

// --------------------------------------------------- //

void  Suffer::Interface::End(){

}

// --------------------------------------------------- //

void Suffer::Interface::DrawMenuBar(){

	ImGui::BeginMainMenuBar();

	// FILE
	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("Close")) {
			// Close the program
		}
		ImGui::EndMenu();
	}

	// OPTIONS
	if (ImGui::BeginMenu("Tools")) {
		if (ImGui::MenuItem("Options")) {
			options_window_ = !options_window_;
		}
		ImGui::EndMenu();
	}

	// WINDOWS
	if (ImGui::BeginMenu("Windows")) {
		if (ImGui::MenuItem("Hierarchy")) {
			is_hierarchy_opened_ = !is_hierarchy_opened_;
		}
		if (ImGui::MenuItem("Inspector")) {
			is_inspector_opened_ = !is_inspector_opened_;
		}
		if (ImGui::MenuItem("Project")) {
			is_project_window_opened_ = !is_project_window_opened_;
		}
		if (ImGui::MenuItem("Game")) {
			is_game_window_opened_ = !is_game_window_opened_;
		}
		if (ImGui::MenuItem("Log")) {
			is_log_opened_ = !is_log_opened_;
		}
		if (ImGui::MenuItem("Audio")) {
			is_audio_window_opened_ = !is_audio_window_opened_;
		}
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();

}

// --------------------------------------------------- //

void  Suffer::Interface::CreateDock(bool* p_open){

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


	if (ImGui::DockBuilderGetNode(ImGui::GetID("SufferDockSpace")) == NULL){

		// DockSpace
		ImGuiID dockspace_id = ImGui::GetID("SufferDockSpace");

		ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
		ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags); // Add empty node
		ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);
		ImGui::SetNextWindowBgAlpha(0.0f);

		ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
		ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.15f, NULL, &dock_main_id);
		ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.20f, NULL, &dock_main_id);
		ImGuiID dock_id_top = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.65f, NULL, &dock_main_id);
		ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

		ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
		ImGui::DockBuilderDockWindow("Hierarchy", dock_id_left);
		ImGui::DockBuilderDockWindow("Project", dock_id_bottom);
		ImGui::DockBuilderDockWindow("Audio", dock_id_bottom);
		ImGui::DockBuilderDockWindow("Log", dock_id_bottom);
		ImGui::DockBuilderDockWindow("Game", dock_id_top);
		ImGui::DockBuilderFinish(dockspace_id);
		
	}

	ImGui::DockSpace(ImGui::GetID("SufferDockSpace"), ImVec2(0.0f, 0.0f), dockspace_flags);

	if(is_inspector_opened_) Inspector();
	if(is_hierarchy_opened_) Hierarchy(SufferManager::instance().GetCurrentScene());
	if(is_project_window_opened_) Project();
	if(is_log_opened_) Log();
  s32 id = 0;//suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[suffer.render_manager_.frame_buffer_id_].color_texture_id_].current_texture_id_;
	if (is_game_window_opened_) Game(id);
	

	ImGui::End();

}

// --------------------------------------------------- //

void  Suffer::Interface::ResetDock(){

}

// --------------------------------------------------- //

void  Suffer::Interface::OpenWindows(){

	if (options_window_) Options();

}

// --------------------------------------------------- //

void  Suffer::Interface::ChangeEditorStyle(){

	ImGuiStyle& new_style_ = ImGui::GetStyle();
	#define COL(v, b, n) ImVec4(v / 255.0f, b / 255.0f, n / 255.0f, 100.0f);

	switch (style_){
		case Interface::kInterfaceStyle_Default: {
			ImGui::StyleColorsDark();
			break;
		}
		case Interface::kInterfaceStyle_Dark: {

			new_style_.FrameBorderSize = 1.0f;
			new_style_.FramePadding = ImVec2(4.0f, 2.0f);
			new_style_.ItemSpacing = ImVec2(8.0f, 2.0f);
			new_style_.WindowBorderSize = 1.0f;
			new_style_.TabBorderSize = 1.0f;
			new_style_.WindowRounding = 1.0f;
			new_style_.ChildRounding = 1.0f;
			new_style_.FrameRounding = 1.0f;
			new_style_.ScrollbarRounding = 1.0f;
			new_style_.GrabRounding = 1.0f;
			new_style_.TabRounding = 1.0f;

			// Setup style
			ImVec4* colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 0.95f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.12f, 0.12f, 1.00f);
			colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.94f);
			colors[ImGuiCol_Border] = ImVec4(0.53f, 0.53f, 0.53f, 0.46f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.85f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.22f, 0.40f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 0.53f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.48f, 0.47f, 0.47f, 0.91f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.55f, 0.55f, 0.62f);
			colors[ImGuiCol_Button] = ImVec4(0.50f, 0.50f, 0.50f, 0.63f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.67f, 0.68f, 0.63f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.26f, 0.26f, 0.26f, 0.63f);
			colors[ImGuiCol_Header] = ImVec4(0.54f, 0.54f, 0.54f, 0.58f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.64f, 0.65f, 0.65f, 0.80f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 0.80f);
			colors[ImGuiCol_Separator] = ImVec4(0.58f, 0.58f, 0.58f, 0.50f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.64f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.81f, 0.81f, 0.81f, 0.64f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.87f, 0.87f, 0.87f, 0.53f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);
			colors[ImGuiCol_Tab] = ImVec4(0.01f, 0.01f, 0.01f, 0.86f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
			colors[ImGuiCol_TabActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
			colors[ImGuiCol_DockingPreview] = ImVec4(0.38f, 0.48f, 0.60f, 1.00f);
			colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
			colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.68f, 0.68f, 0.68f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.77f, 0.33f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.87f, 0.55f, 0.08f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.47f, 0.60f, 0.76f, 0.47f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(0.58f, 0.58f, 0.58f, 0.90f);
			colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

			break;
		}
		case Interface::kInterfaceStyle_Red: {

			new_style_.FrameBorderSize = 1.0f;
			new_style_.FramePadding = ImVec2(4.0f, 2.0f);
			new_style_.ItemSpacing = ImVec2(8.0f, 2.0f);
			new_style_.WindowBorderSize = 1.0f;
			new_style_.TabBorderSize = 1.0f;
			new_style_.WindowRounding = 1.0f;
			new_style_.ChildRounding = 1.0f;
			new_style_.FrameRounding = 1.0f;
			new_style_.ScrollbarRounding = 1.0f;
			new_style_.GrabRounding = 1.0f;
			new_style_.TabRounding = 1.0f;

			// Setup style
			ImVec4* colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_Text] = COL(200.0f, 200.0f, 200.0f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			colors[ImGuiCol_WindowBg] = COL(29.0f, 29.0f, 29.0f);
			colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.94f);
			colors[ImGuiCol_Border] = ImVec4(0.53f, 0.53f, 0.53f, 0.46f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.85f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.22f, 0.40f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 0.53f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
			colors[ImGuiCol_MenuBarBg] = COL(54.0f, 54.0f, 54.0f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.48f, 0.47f, 0.47f, 0.91f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.55f, 0.55f, 0.62f);
			colors[ImGuiCol_Button] = ImVec4(0.50f, 0.50f, 0.50f, 0.63f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.67f, 0.68f, 0.63f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.26f, 0.26f, 0.26f, 0.63f);
			colors[ImGuiCol_Header] = ImVec4(0.54f, 0.54f, 0.54f, 0.58f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.64f, 0.65f, 0.65f, 0.80f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 0.80f);
			colors[ImGuiCol_Separator] = ImVec4(0.58f, 0.58f, 0.58f, 0.50f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.64f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.81f, 0.81f, 0.81f, 0.64f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.87f, 0.87f, 0.87f, 0.53f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);
			colors[ImGuiCol_Tab] = COL(100.0f, 100.0f, 100.0f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
			colors[ImGuiCol_TabActive] = COL(192.0f, 38.0f, 38.0f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
			colors[ImGuiCol_TabUnfocusedActive] = COL(192.0f, 38.0f, 38.0f);
			colors[ImGuiCol_DockingPreview] = ImVec4(0.38f, 0.48f, 0.60f, 1.00f);
			colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
			colors[ImGuiCol_PlotLines] = COL(204.0f, 82.0f, 122.0f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.68f, 0.68f, 0.68f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = COL(232.0f, 23.0f, 92.0f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.87f, 0.55f, 0.08f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.47f, 0.60f, 0.76f, 0.47f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(0.58f, 0.58f, 0.58f, 0.90f);
			colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

			break;
		}
		case Interface::kInterfaceStyle_White: {
			ImGui::StyleColorsLight();
			break;
		}
		case Interface::kInterfaceStyle_RayTeak: {

			new_style_.WindowPadding = ImVec2(15, 15);
			new_style_.WindowRounding = 12.0f;
			new_style_.WindowBorderSize = 0.0f;
			new_style_.ChildBorderSize = 0.0f;
			new_style_.PopupBorderSize = 0.0f;
			new_style_.FrameBorderSize = 0.0f;
			new_style_.TabBorderSize = 0.0f;
			new_style_.TabRounding = 6.0f;
			new_style_.FrameRounding = 7.0f;
			new_style_.FramePadding = ImVec2(5, 5);
			new_style_.FrameRounding = 4.0f;
			new_style_.ItemSpacing = ImVec2(12, 8);
			new_style_.ItemInnerSpacing = ImVec2(8, 6);
			new_style_.IndentSpacing = 25.0f;
			new_style_.ScrollbarSize = 15.0f;
			new_style_.ScrollbarRounding = 9.0f;
			new_style_.GrabMinSize = 5.0f;
			new_style_.GrabRounding = 3.0f;

			ImVec4* colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.93f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			colors[ImGuiCol_CheckMark] = COL(255.0f, 50.0f, 50.0f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			colors[ImGuiCol_PlotLines] = COL(204.0f, 82.0f, 122.0f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = COL(232.0f, 23.0f, 92.0f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
			colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

			break;
		}
		case Interface::kInterfaceStyle_Commodore64:
			break;
		default:
			break;
	}

}

// --------------------------------------------------- //

void  Suffer::Interface::Hierarchy(Scene* current_scene_){

#ifdef ASSERT
    assert(current_scene_ != nullptr && "NULL Scene!");
#endif

	ImGui::Begin("Hierarchy", &is_hierarchy_opened_);
	ImGui::Text("Scene Hierarchy");

  u32 scene_game_objects = current_scene_->current_gameobjects_.size();

  for (int i = 0; i < scene_game_objects; ++i) {
      u32 number_of_childs = current_scene_->current_gameobjects_.at(i).get()->NumberChilds();
      if (ImGui::CollapsingHeader(current_scene_->current_gameobjects_.at(i).get()->Name())) {
          for (int i = 0; i < number_of_childs; ++i) {
              if (ImGui::TreeNode("Childs")) {
                  ImGui::TreePop();
              }
          }
      }
  }

	ImGui::End();

}

// --------------------------------------------------- //

void  Suffer::Interface::Log() {
	log.Draw("Log", &is_log_opened_);
}

// --------------------------------------------------- //

void  Suffer::Interface::Inspector(){
	ImGui::Begin("Inspector", &is_inspector_opened_);
	ImGui::Text("I'm the Inspector");

	if (!ImGui::CollapsingHeader("GO_Attributes")) {
		for (int i = 0; i < 20; ++i) {
			if (ImGui::TreeNode("Attributes_")) {
				ImGui::TreePop();
			}
		}
	}

	ImGui::End();
}

// --------------------------------------------------- //

void  Suffer::Interface::Project(){
	ImGui::Begin("Project", &is_project_window_opened_);
	ImGui::Text("I'm the project structure!");
	ImGui::End();
}

// --------------------------------------------------- //

void  Suffer::Interface::Audio(Audio3D* sound){

	static char buffer[255] = "\0";
	static char pre_buffer_[255] = "../../../resources/audio/";
	static char aux_buffer[255] = "../../../resources/audio/";
	static bool swiped = false;
  static bool sound_active_ = sound->active_;
	static int max_value = 256;
  static int sounds_id = 0;

  std::string attributes_ = "\0";

	ImGui::Begin("Audio Tests");

  float song_volume = sound->GetGain();
  static mathmorra::Vector3 song_position = sound->GetSoundPosition();
  static bool looping = sound->GetLooping();
  bool paused = sound->isPaused();

  // Attributes
  ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), sound->name_);

  attributes_ = sound->name_;
  attributes_.append(" volume");
  if (ImGui::SliderFloat(attributes_.c_str(), &song_volume, 0.0f, 2.0f)) {
    sound->SetGain(song_volume);
  }
  if (ImGui::InputFloat3("Sound Position", &song_position.x_, 0.1f)) {
    sound->SetSoundPosition(song_position);
  }
  if (paused) {
    if (ImGui::Button("Play")) {
      ref_ptr<AudioCommands::Play> play_command_;
      play_command_.alloc();
      play_command_->audio_3d_ = sound;
      //suffer.AddCommand(&suffer.audio_dl_, play_command_.get());
      play_command_.release();
    }
  }
  else {
    if (ImGui::Button("Pause")) {
      ref_ptr<AudioCommands::Pause> pause_command_;
      pause_command_.alloc();
      pause_command_->audio_3d_ = sound;
      //suffer.AddCommand(&suffer.audio_dl_, pause_command_.get());
      pause_command_.release();
    }
  }
  ImGui::SameLine();
  if (ImGui::Checkbox("Looping", &looping)) {
    sound->SetLooping(looping);
  }

  ImGui::SameLine();
  ImGui::PushID(sounds_id);
  if (ImGui::Checkbox("Is Active", &sound_active_)) {
    sound->SetActive(sound_active_);
  }
  sounds_id++;
  ImGui::PopID();

  if (sounds_id > MAX_SAMPLES) sounds_id = 0;

	ImGui::InputText("Song", buffer, sizeof(buffer));
	ImGui::SameLine();
	if (ImGui::Button("Load")) {
		strcat(pre_buffer_, buffer);
		sound->Load(pre_buffer_);
		for (int i = 0; i < sizeof(buffer); ++i) buffer[i] = '\0';
		strcpy(pre_buffer_, aux_buffer);
	}

	ImGui::Spacing();
	float* buf = sound->Wave();
	float* fft = sound->FFT();

	// Diagrams
	if (ImGui::Button("Swipe")) swiped = !swiped;
	ImGui::SameLine();
	ImGui::SliderInt("Graphic values", &max_value, 0, 256);
	if (!swiped) {
		ImGui::PlotHistogram("##Wave", buf, max_value, 0, "Wave", -1, 1, ImVec2(264, 80));
		ImGui::SameLine();
		ImGui::PlotHistogram("##Fast Fourier Transform (FFT)", fft, max_value * 0.5f, 0, "FFT", 0, 10, ImVec2(264, 80), 8);
	}
	else {
		ImGui::PlotLines("##Wave", buf, max_value, 0, "Wave", -1, 1, ImVec2(264, 80));
		ImGui::SameLine();
		ImGui::PlotLines("##Fast Fourier Transform (FFT)", fft, max_value * 0.5f, 0, "FFT", 0, 10, ImVec2(264, 80), 8);
	}
	ImGui::Separator();

	ImGui::End();

}

// --------------------------------------------------- //

void  Suffer::Interface::Game(s32 tex){

#ifdef ASSERT
	assert(tex >= 0 && "Texture ID not valid.\n");
#endif

	ImGui::Begin("Game", &is_game_window_opened_);

	if (tex > 0) {
		int width = ImGui::GetWindowWidth();
		int height = ImGui::GetWindowHeight();

		ImVec2 vec = ImGui::GetWindowPos();
		ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)tex, vec, ImVec2(vec.x + width, vec.y + height));
	}

	ImGui::Text("I'm the Game!!");
	ImGui::End();

}

// --------------------------------------------------- //

void  Suffer::Interface::Options(){

	static int styleSelection = (int)style_;

	ImGui::Begin("Options");

	if (ImGui::Combo("ImGui Style", &styleSelection, styles, IM_ARRAYSIZE(styles))) {
		style_ = (InterfaceStyle)styleSelection;
		ChangeEditorStyle();
	}

	ImGui::End();

}

// --------------------------------------------------- //
