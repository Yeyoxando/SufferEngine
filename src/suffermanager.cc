#include <suffermanager.h>
#include <imgui.h>
#include <input.h>
#include <window.h>
#include "imgui_impl_opengl3.h"
#include <interface.h>
#include <clear.h>
#include <time.h>
#include <GLFW/glfw3.h>

// --------------------------------------------------------------//

struct SufferManager::Data {

	ref_ptr<Scene> scene_;
	Suffer::Window wind_;
	double previous_time_;
	double current_time_;
	double delta_time_;
	Interface interface_;

	// Mutexes
  Mutex audio_mutex;
  Mutex render_mutex;
	
	// Running
	bool window_should_close_;
	

};

// --------------------------------------------------------------//

SufferManager::SufferManager(){

	data_ = new Data();

	//data_->display_list_ = std::vector<ref_ptr<Command>>(0);
	audio_dl_ = std::vector<ref_ptr<Command>>(0);
	data_->scene_.alloc();

}

// --------------------------------------------------------------//

SufferManager::~SufferManager(){
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------------------//

SufferManager::SufferManager(const SufferManager&){

}

// --------------------------------------------------------------//

SufferManager& SufferManager::instance() {

	static SufferManager* instance = new SufferManager();
	return *instance;

}

// --------------------------------------------------------------//

bool SufferManager::Init(){

#ifdef ASSERT
	assert(data_ && "\n Data is null.");
#endif // ASSERT

	data_->wind_.init(800, 600);
	Suffer::InitInput();
	data_->interface_.Init();

	//Subsystems init
	render_manager_.StartUp();
  resource_manager_.StartUp();


	// Threads Allocation
	logic_.alloc();
	input_.alloc();
	audio_.alloc();

	// Threads Function Assignment
	auto audio_thread = [] { SufferManager::instance().Audio(); };
	audio_.get()->NewTask(audio_thread);

	auto update_thread = [] { SufferManager::instance().Update(); };
	logic_.get()->NewTask(update_thread);

	auto input_thread = [] { SufferManager::instance().Input(); };
	input_.get()->NewTask(input_thread);


	//data_->InitInternalMaterials();
	//data_->InitInternalGeometries();

	data_->window_should_close_ = false;


	data_->scene_->Init();
	//newSong.alloc();

	return true;
}

// --------------------------------------------------------------//

void SufferManager::Update() {

	while(1){
		Step(data_->delta_time_);
		logic_->Sleep();
	}

}

// --------------------------------------------------------------//

void SufferManager::Draw() {

	data_->interface_.Update();
	data_->interface_.Render();

	render_manager_.DoRender();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	data_->wind_.swapBuffers();

}

// --------------------------------------------------------------//

void SufferManager::Input() {

	while (1) {
		input_->Sleep();

		// Window Should Close
		if (Suffer::IsKeyDown(k_Escape)) {
			data_->window_should_close_ = true;
		}
	}

}

// --------------------------------------------------------------//

bool SufferManager::Run(){

	while (!data_->window_should_close_) {

		data_->current_time_ = Suffer::RawTime();
		data_->wind_.processEvents();
		
		input_->Awake();
		
    logic_->Awake();

		Draw();
    
    logic_->WaitMe();

		data_->delta_time_ = (data_->current_time_ - data_->previous_time_) * 0.0001f;
		data_->previous_time_ = data_->current_time_;

	}

	return true;

}

// --------------------------------------------------------------//

void SufferManager::Audio() {

	while (1) {

		audio_->Sleep();

		if (!data_->audio_mutex.try_lock()) {
	#ifdef DEBUG
			printf("\nError trying to lock the audio_mutex: [%s]\n", __FUNCTION__);
	#endif
			return;
		}

		int display_list_size = audio_dl_.size();

		for (int i = 0; i < display_list_size; ++i) {
			Command* audio_command = audio_dl_[i].get();
	#ifdef ASSERT
			assert(audio_command && "NULL Audio Command");
	#endif
			audio_command->Execute();
		}
	
		audio_dl_.clear();

		data_->audio_mutex.unlock();

	}
}

// --------------------------------------------------------------//

void SufferManager::PrepareAudio() {
	
	if (!audio_dl_.empty()) {
		audio_->Awake();
	}

}

// --------------------------------------------------------------//

bool SufferManager::Step(double time_step){

	//PrepareDraw();
	data_->scene_->Step(time_step);
	// This will be the last function in UPDATE
	PrepareAudio();

	return true;
}

// --------------------------------------------------------------//

bool SufferManager::Finish(){

	//resource_manager_.ShutDown();
	render_manager_.ShutDown();

	return true;
}

// --------------------------------------------------------------//

double SufferManager::DeltaTime(){

#ifdef ASSERT
	assert(data_ && "\n Data is null.");
#endif // ASSERT
	return data_->delta_time_;

}
