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
#include "system_render.h"
#include "system_transform.h"

// --------------------------------------------------------------//

Suffer::SufferManager::SufferManager(){

	data_ = new Data();
	data_->scene_context_.alloc();
  audio_mode_ = 0;

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

void Suffer::SufferManager::AddSystem(System* new_system){
  assert(new_system != nullptr && "NULL System");
  systems_.push_back(new_system);
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

  // Adding systems
  transform_system_.alloc();
  suffer.AddSystem(transform_system_.get());

  render_system_.alloc();
  suffer.AddSystem(render_system_.get());

  // High Level Stuff
  one.alloc(); two.alloc();
  one->Load("../../../resources/audio/wing_cap.ogg");
  two->Load("../../../resources/audio/monster_town.ogg");
  ref_ptr<Suffer::AudioCommands::Play> play_one;
  ref_ptr<Suffer::AudioCommands::Play> play_two;
  play_one.alloc(); play_two.alloc();
  play_one->audio_3d_ = one.get();
  play_two->audio_3d_ = two.get();
  suffer.audio_manager_.audio_dl_.AddCommand(play_one.get());
  suffer.audio_manager_.audio_dl_.AddCommand(play_two.get());



  for (int i = 0; i < MAX_SAMPLES; ++i) {
    samples_[i].alloc();
    samples_[i]->SetLooping(true);
  }

  samples_[0]->Load("../../../resources/audio/samples/up_and_abobe_BASS.ogg");
  samples_[1]->Load("../../../resources/audio/samples/up_and_abobe_DRUMS.ogg");
  samples_[2]->Load("../../../resources/audio/samples/up_and_abobe_INSTRUMENTS.ogg");
  samples_[3]->Load("../../../resources/audio/samples/up_and_abobe_MELODY.ogg");

  samples_[0]->name_ = "BASS";
  samples_[1]->name_ = "DRUMS";
  samples_[2]->name_ = "INSTRUMENTS";
  samples_[3]->name_ = "MELODY";

  samples_[0]->Play3D();
  samples_[1]->Play3D();
  samples_[2]->Play3D();
  samples_[3]->Play3D();

  one->SetLooping(true);
  two->SetLooping(true);
  // TODO: Delete this

	return true;

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Draw() {

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

  if (input_manager_.IsKeyDown(InputManager::k_Y) && suffer.audio_mode_ == 0) {
    ref_ptr<Suffer::AudioCommands::Crossfade> crossfade_;
    crossfade_.alloc();
    crossfade_->attenuation_ = 0.0001f;
    crossfade_->from_ = one.get();
    crossfade_->to_ = two.get();
    suffer.audio_manager_.audio_dl_.AddCommand(crossfade_.get());
  }

  if (input_manager_.IsKeyDown(InputManager::k_U) && suffer.audio_mode_ == 0) {
    ref_ptr<Suffer::AudioCommands::Crossfade> crossfade_;
    crossfade_.alloc();
    crossfade_->from_ = two.get();
    crossfade_->to_ = one.get();
    suffer.audio_manager_.audio_dl_.AddCommand(crossfade_.get());
  }

  if (input_manager_.IsKeyDown(InputManager::k_Keypad_1)) {
    audio_mode_ = 0;
    for (u32 i = 0; i < MAX_SAMPLES; ++i) {
      samples_[i].get()->SetPaused(true);
    }

    one->SetPaused(false);
    two->SetPaused(false);
  }

  if (input_manager_.IsKeyDown(InputManager::k_Keypad_2)) {
    audio_mode_ = 1;
    one->SetPaused(true);
    two->SetPaused(true);

    for (u32 i = 0; i < MAX_SAMPLES; ++i) {
      samples_[i].get()->SetPaused(false);
    }

  }

  if (input_manager_.IsKeyDown(InputManager::k_Keypad_3)) {
    audio_mode_ = 2;
    one->SetGain(0.0f);
    two->SetGain(0.0f);
  }

  input_manager_.Update();

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Run() {

  // Threads Function Assignment
  auto update_thread = [] { SufferManager::instance().Step(); };
  auto input_thread = [] { SufferManager::instance().Input(); };

  logic_->NewTask(update_thread);

  one->SetGain(0.0f);
  samples_[0]->SetPaused(true);
  samples_[1]->SetPaused(true);
  samples_[2]->SetPaused(true);
  samples_[3]->SetPaused(true);

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

void Suffer::SufferManager::HighLevel(){




}

// --------------------------------------------------------------//

void Suffer::SufferManager::Step(){

	data_->scene_context_->Step(data_->delta_time_);

  // Systems
  u32 systems_size = systems_.size();
  u32 game_objects_count = suffer.GetCurrentScene()->current_gameobjects_.size();
  for (u32 i = 0; i < systems_size; ++i) {
    for (u32 j = 0; j < game_objects_count; ++j) {
      systems_[i]->Execute(suffer.GetCurrentScene()->current_gameobjects_[j].get());
    }
  }

  render_manager_.AddToRenderQueue(std::move(render_system_.get()->dl_));

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

