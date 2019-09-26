#include <stdio.h>
#include <GL/glew.h>
#include <window.h>
#include <glm.hpp>

// This will be removed
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "glfw3.h"

// --------------------------------------------------------------//

void TestingGLM() {

	glm::vec4 vector_1 = { 1.0f, 1.0f, 1.0f, 1.0f };
	vector_1 *= glm::vec4(2, 2, 2, 2);
	
	float fModule = vector_1.length();
	vector_1 = glm::normalize(vector_1);

	glm::vec4 negative = { -1.0f, -1.0f, -1.0f, -1.0f };
	negative += glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

}

// --------------------------------------------------------------//

void InitImGui() {

	ImGui::CreateContext();

	ImGuiIO io = ImGui::GetIO(); (void)io;

	// ImGui FLAGS
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	io.ConfigViewportsNoAutoMerge = true;
	io.ConfigViewportsNoTaskBarIcon = true;

	io.Fonts->AddFontDefault();
	io.Fonts->Build();
	ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

}

// --------------------------------------------------------------//

void TestingImGui() {

	static bool show_demo_window = true;

    ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow(&show_demo_window);

	// Rendering
	ImGui::Render();

	int display_w, display_h;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &display_w, &display_h);

	glViewport(0, 0, display_w, display_h);

	ImGui::EndFrame();



}

// --------------------------------------------------------------//

void Clear() {

	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	glfwSwapBuffers(glfwGetCurrentContext());

}

// --------------------------------------------------------------//

int main(int argc, char *argv[]) {

	TestingGLM();

	Suffer::Window wind;

	wind.init(800, 600);
	if (glewInit() != GLEW_OK) {
		return 1;
	}

	InitImGui();

	while(1){
		glfwPollEvents();
		TestingImGui();
		Clear();
	}

	return 0;
}

// --------------------------------------------------------------//