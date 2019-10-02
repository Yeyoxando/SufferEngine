#include <stdio.h>

#include <window.h>
#include <glm.hpp>
#include <time.h>
#include <sokol_time.h>

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

void TestingImGui() {

	double timer = Suffer::RawTime();

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

	double current = Suffer::RawTime() - timer;

}

// --------------------------------------------------------------//

void Clear() {

	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(glfwGetCurrentContext());

}

// --------------------------------------------------------------//

int main(int argc, char *argv[]) {

	stm_setup();

	uint64_t start = stm_now();
	TestingGLM();
	uint64_t end = stm_now();
	uint64_t elapsed = stm_diff(end, start);

	Suffer::Window wind;

	wind.init(800, 600);

	double previous_time = 0.0f;

	while(1){

		double currentTime = Suffer::RawTime();

		wind.processEvents();
		TestingImGui();
		Clear();

		float deltaTime = (currentTime - previous_time) * 0.0001f;
		previous_time = currentTime;

	}

	return 0;
}

// --------------------------------------------------------------//