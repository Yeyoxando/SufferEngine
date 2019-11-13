#include "suffermanager.h"
#include "imgui.h"
#include "input.h"
#include "window.h"
#include "imgui_impl_opengl3.h"
#include "interface.h"
#include "common_definitions.h"
#include "time.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "scene.h"
#include "audio_commands.h"
#include "internal_suffermanager.h"
#include <string>

// --------------------------------------------------------------//

Suffer::SufferManager::SufferManager(){

	data_ = new Data();
	data_->scene_context_.alloc();

}

// --------------------------------------------------------------//

Suffer::SufferManager::~SufferManager(){
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------------------//

Suffer::SufferManager::SufferManager(const SufferManager&){

}

// --------------------------------------------------------------//

Suffer::SufferManager& Suffer::SufferManager::instance() {

	static SufferManager* instance = new SufferManager();
	return *instance;

}

// --------------------------------------------------------------//

bool Suffer::SufferManager::Init(){

#ifdef ASSERT
	assert(data_ && "\n Data is null.");
#endif // ASSERT

	data_->wind_.init(WINDOW_WIDTH, WINDOW_HEIGHT);
	//Suffer::InitInput();
	data_->interface_.Init();
  data_->is_interface_active_ = false;

	//Subsystems init
  audio_manager_.StartUp();
  render_manager_.StartUp();
  resource_manager_.StartUp();
  input_manager_.StartUp();

	// Threads Allocation
	logic_.alloc();
	input_.alloc();
	audio_.alloc();



	data_->window_should_close_ = false;

	data_->scene_context_->Init();

	return true;
}

// --------------------------------------------------------------//

void Suffer::SufferManager::Update() {

    Step(data_->delta_time_);

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Draw() {

	render_manager_.DoRender();

  if (data_->is_interface_active_) {
      data_->interface_.Update();
      data_->interface_.Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

	data_->wind_.swapBuffers();

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Input() {

		// Window Should Close
    if (input_manager_.IsKeyDown(InputManager::k_Escape)) {
        data_->window_should_close_ = true;
    }

    // Activate Interface
    if (input_manager_.IsKeyDown(InputManager::k_F2)) {
        data_->is_interface_active_ = !data_->is_interface_active_;
    }

}

// --------------------------------------------------------------//

bool Suffer::SufferManager::Run(){

  //ref_ptr<Audio3D> audio_source_;
  //audio_source_.alloc();
  //audio_source_->Load("../../../resources/audio/plonk_dry.ogg");
  //ref_ptr <AudioCommands::Play> play_command_;
  //play_command_.alloc();
  //play_command_->audio_3d_ = audio_source_.get();
  //DisplayList audio_dl_;
  //audio_dl_.addCommand(play_command_.get());
  //audio_manager_.AddToAudioQueue(std::move(audio_dl_));

  // Threads Function Assignment
  auto update_thread = [] { SufferManager::instance().Update(); };
  auto input_thread = [] { SufferManager::instance().Input(); };

  logic_->NewTask(update_thread);

	while (!data_->window_should_close_) {

    // TODO: remove from here
    SetMousePosition();

		data_->current_time_ = Suffer::RawTime();
		data_->wind_.processEvents();
		
    // TODO: remove this thread
		input_->NewTask(input_thread);
		
    logic_->NewTask(update_thread);

		Draw();
    
    logic_->WaitFor(logic_.get());

		data_->delta_time_ = (data_->current_time_ - data_->previous_time_) * 0.0001f;
		data_->previous_time_ = data_->current_time_;

	}

	return true;

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Audio() {

    audio_manager_.DoAudio();

}

// --------------------------------------------------------------//

void Suffer::SufferManager::PrepareAudio() {
	
    if (audio_manager_.audio_dl_.size() > 0) {
        auto audio_thread = [] { SufferManager::instance().Audio(); };
        audio_->NewTask(audio_thread);
    }

}

// --------------------------------------------------------------//

bool Suffer::SufferManager::Step(double time_step){

	data_->scene_context_->Step(time_step);

	// This will be the last function in UPDATE
	PrepareAudio();

	return true;
}

// --------------------------------------------------------------//

bool Suffer::SufferManager::Finish(){

  resource_manager_.ShutDown();
	render_manager_.ShutDown();
  audio_manager_.ShutDown();
  input_manager_.ShutDown();

	return true;
}

// --------------------------------------------------------------//

double Suffer::SufferManager::DeltaTime(){

#ifdef ASSERT
	assert(data_ && "\n Data is null.");
#endif // ASSERT
	return data_->delta_time_;

}

// --------------------------------------------------------------//

mathmorra::Vector2 Suffer::SufferManager::GetMousePosition(){
    return mouse_position_;
}

// --------------------------------------------------------------//

void Suffer::SufferManager::SetMousePosition(){

    //mouse_position_.x_ = Suffer::MousePositionX();
    //mouse_position_.y_ = Suffer::MousePositionY();

}

// --------------------------------------------------------------//

Suffer::Scene* Suffer::SufferManager::GetCurrentScene() {
    return data_->scene_context_.get();
}

// --------------------------------------------------------------//

