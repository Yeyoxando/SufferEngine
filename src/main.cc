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
#define PX_SCHED_IMPLEMENTATION 1
#include <px_sched.h>

// --------------------------------------------------------------//

void TestingGLMComplex() {

	glm::mat4x4 first_mat;
	glm::mat4x4 second_mat;
	glm::mat4x4 result;

	uint64_t number_iterations = 100000;

	first_mat = glm::mat4x4(2.0f);
	second_mat = glm::mat4x4(10.0f);

	for (int i = 0; i < number_iterations; ++i) {
		result = first_mat * second_mat;
	}
	
}

// --------------------------------------------------------------//

void TestingGLMSimple() {

	glm::mat4x4 first_mat;
	glm::mat4x4 second_mat;
	glm::mat4x4 result;

	first_mat = glm::mat4x4(2.0f);
	second_mat = glm::mat4x4(10.0f);

	result = first_mat * second_mat;

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
	uint32_t number_iterations = 100;

	//Warming processor
	for (int i = 0; i < 10; ++i) {
		TestingGLMComplex();
	}

	uint64_t start = stm_now();
	for (int i = 0; i < number_iterations; ++i) {
		TestingGLMComplex();
	}
	uint64_t end = stm_now();
	uint64_t elapsed = stm_diff(end, start);
	double elapsed_2 = stm_ms(elapsed);

	px_sched::Scheduler scheduler;
	scheduler.init();
	px_sched::Sync sync;
	start = stm_now();
	for (int i = 0; i < number_iterations; ++i) {
		scheduler.run(TestingGLMComplex, &sync);
	}
	scheduler.waitFor(sync);
	end = stm_now();
	elapsed = stm_diff(end, start);
	double elapsed_3 = stm_ms(elapsed);


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