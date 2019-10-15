#include <stdio.h>

#include <window.h>
#include <glm.hpp>
#include <time.h>
#include <chrono.h>

// This will be removed
#include <imgui.h>
#include <scene.h>
#include <game_object.h>
#include <suffermanager.h>
#include <clear.h>
#include <input.h>
#include <interface.h>
#include <vector>
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

void PrepareDraw() {
	EDK3::ref_ptr<Clear> clear_cmd;

	clear_cmd.alloc();

	//int rnd = rand()%10;
	//float frnd = rnd / 10.0f;
	//clear_cmd->SetClearColor(glm::vec4(frnd));
	
	clear_cmd->SetClearColor(glm::vec4(0.8f));

	SufferManager::instance().AddCommand(clear_cmd.get());

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
	SufferManager& suffer_manager = SufferManager::instance();

	wind.init(800, 600);
	Suffer::InitInput();

	double previous_time = 0.0f;

	while(!Suffer::IsKeyDown(k_Escape)){

		double currentTime = Suffer::RawTime();
		wind.processEvents();
		//interface_.Update();
		PrepareDraw();

		suffer_manager.DrawDisplayList();

		float deltaTime = (currentTime - previous_time) * 0.0001f;
		previous_time = currentTime;

	}

	return 0;
}

// --------------------------------------------------------------//