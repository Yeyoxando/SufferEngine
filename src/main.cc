#include <stdio.h>

#include <window.h>
#include <glm.hpp>
#include <time.h>
#include <chrono.h>

// This will be removed
#include <imgui.h>
#include <scene.h>
#include <game_object.h>
#include <interface.h>
#include <vector>
#include <imgui_impl_opengl3.h>
#include "glfw3.h"
#include <px_sched.h>

// --------------------------------------------------------------//

void TestingGLMComplex(int x) {

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

	Chrono chrono_;
	uint32_t number_iterations = 100;
	Scene sc;
	Interface interface_;

	////Warming processor
	//for (int i = 0; i < 10; ++i) {
	//	TestingGLMComplex(1);
	//}
	//
	//uint64_t start = chrono_.Now();
	//for (int i = 0; i < number_iterations; ++i) {
	//	TestingGLMComplex(1);
	//}
	//uint64_t end = chrono_.Now();
	//uint64_t elapsed = chrono_.Difference(end, start);
	//double elapsed_2 = chrono_.ToMilliseconds(elapsed);
	//
	//px_sched::Scheduler scheduler;
	//scheduler.init();
	//px_sched::Sync sync;
	//start = chrono_.Now();
	//for (int i = 0; i < number_iterations; ++i) {
	//	scheduler.run([i] {TestingGLMComplex(i); }, &sync);
	//}
	//scheduler.waitFor(sync);
	//end = chrono_.Now();
	//elapsed = chrono_.Difference(end, start);
	//double elapsed_3 = chrono_.ToMilliseconds(elapsed);


	Suffer::Window wind;

	wind.init(800, 600);

	double previous_time = 0.0f;

	while(1){

		double currentTime = Suffer::RawTime();
		wind.processEvents();
		interface_.Update();
		Clear();

		float deltaTime = (currentTime - previous_time) * 0.0001f;
		previous_time = currentTime;

	}

	return 0;
}

// --------------------------------------------------------------//