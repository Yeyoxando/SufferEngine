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

	assert(data_ && "\n Data is null.");

	data_->wind_.Open(WINDOW_WIDTH, WINDOW_HEIGHT);
	data_->interface_.Init();
  data_->is_interface_active_ = false;
	data_->window_should_close_ = false;

	//Subsystems init
  audio_manager_.StartUp();
  render_manager_.StartUp();
  resource_manager_.StartUp();
  input_manager_.StartUp();

	// Threads Allocation
	logic_.alloc();
	input_.alloc();
	audio_.alloc();

	return true;

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Draw() {

 if (suffer.input_manager_.IsKeyDown(InputManager::k_F1)) {
     glfwSetCursorPos(glfwGetCurrentContext(), WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);
 }

	render_manager_.DoRender();

  if (data_->is_interface_active_) {
      data_->interface_.Update();
      data_->interface_.Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

	data_->wind_.SwapBuffers();

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

  input_manager_.Update();

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Run(){

  //ref_ptr<Audio3D> one;
  //ref_ptr<Audio3D> two;
  //one.alloc(); two.alloc();
  //one->Load("../../../resources/audio/plonk_dry.ogg");
  //two->Load("../../../resources/audio/plonk_wet.ogg");
  //ref_ptr<Suffer::AudioCommands::Play> play_one;
  //ref_ptr<Suffer::AudioCommands::Play> play_two;
  //play_one.alloc(); play_two.alloc();
  //play_one->audio_3d_ = one.get();
  //play_two->audio_3d_ = two.get();
  //play_two->audio_3d_->SetGain(0.0f);
  //suffer.audio_manager_.audio_dl_.AddCommand(play_one.get());
  //suffer.audio_manager_.audio_dl_.AddCommand(play_two.get());
  //Suffer::AudioCommands::Crossfade test();

  //one->SetLooping(true);
  //two->SetLooping(true);

  // Threads Function Assignment
  auto update_thread = [] { SufferManager::instance().Step(); };
  auto input_thread = [] { SufferManager::instance().Input(); };

  logic_->NewTask(update_thread);

	while (!data_->window_should_close_) {

    // TODO: remove from here
    mouse_position_.x_ = input_manager_.MousePositionX();
    mouse_position_.y_ = input_manager_.MousePositionY();

		data_->current_time_ = Suffer::RawTime();
		data_->wind_.ProcessEvents();
		
    // TODO: remove this thread
		input_->NewTask(input_thread);
		
    logic_->NewTask(update_thread);

		Draw();
    
    logic_->WaitFor(logic_.get());

    //if (input_manager_.IsKeyDown(InputManager::k_Y)) {
    //  ref_ptr<Suffer::AudioCommands::Crossfade> crossfade_;
    //  crossfade_.alloc();
    //  crossfade_->attenuation_ = 0.000001f;
    //  crossfade_->from_ = one.get();
    //  crossfade_->to_ = two.get();
    //  suffer.audio_manager_.audio_dl_.AddCommand(crossfade_.get());
    //}
    //
    //if (input_manager_.IsKeyDown(InputManager::k_U)) {
    //  ref_ptr<Suffer::AudioCommands::Crossfade> crossfade_;
    //  crossfade_.alloc();
    //  crossfade_->from_ = two.get();
    //  crossfade_->to_ = one.get();
    //  suffer.audio_manager_.audio_dl_.AddCommand(crossfade_.get());
    //}

		data_->delta_time_ = (data_->current_time_ - data_->previous_time_) * 0.0001f;
		data_->previous_time_ = data_->current_time_;

	}

}

// --------------------------------------------------------------//

void Suffer::SufferManager::SetScene(ref_ptr<Scene> scene){

  assert(scene.get() && "\n Scene is null.");

  data_->scene_context_ = scene;

}
  
// --------------------------------------------------------------//

void Suffer::SufferManager::PrepareAudio() {
	
  if (audio_manager_.audio_dl_.Size() > 0) {
    auto audio_thread = [] { suffer.audio_manager_.DoAudio(); };
    audio_->NewTask(audio_thread);
  }

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Step(){

	data_->scene_context_->Step(data_->delta_time_);

	// This will be the last function in UPDATE
	PrepareAudio();

}

// --------------------------------------------------------------//

bool Suffer::SufferManager::Finish(){
  
  resource_manager_.ShutDown();
	render_manager_.ShutDown();
  audio_manager_.ShutDown();
  input_manager_.ShutDown();

  data_->wind_.Close();

	return true;
}

// --------------------------------------------------------------//

double Suffer::SufferManager::DeltaTime(){

	assert(data_ && "\n Data is null.");

	return data_->delta_time_;

}

// --------------------------------------------------------------//

mathmorra::Vector2 Suffer::SufferManager::GetMousePosition(){

    return mouse_position_;

}

void Suffer::SufferManager::SetCursorPosition(mathmorra::Vector2 newPosition){
    glfwSetCursorPos(glfwGetCurrentContext(), newPosition.x_, newPosition.y_);
}

// --------------------------------------------------------------//

Suffer::Scene* Suffer::SufferManager::GetCurrentScene() {

    return data_->scene_context_.get();

}

// --------------------------------------------------------------//

