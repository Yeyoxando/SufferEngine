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

  red_render_system_.alloc();
  suffer.AddSystem(red_render_system_.get());

  blue_render_system_.alloc();
  suffer.AddSystem(blue_render_system_.get());

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

  input_manager_.Update();

  if (input_manager_.IsKeyDown(InputManager::k_R)) {
    red_render_system_->is_active_ = !red_render_system_->is_active_;
  }
  if (input_manager_.IsKeyDown(InputManager::k_B)) {
    blue_render_system_->is_active_ = !blue_render_system_->is_active_;
  }

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Run() {

  // Threads Function Assignment
  auto update_thread = [] { SufferManager::instance().Step(); };
  auto input_thread = [] { SufferManager::instance().Input(); };

  logic_->NewTask(update_thread);
  logic_->WaitFor(logic_.get());

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

void Suffer::SufferManager::Step(){

  static bool do_once = false;
	data_->scene_context_->Step(data_->delta_time_);

  // Systems
  u32 systems_size = systems_.size();
  u32 game_objects_count = suffer.GetCurrentScene()->current_gameobjects_.size();
  for (u32 i = 0; i < systems_size; ++i) {
    for (u32 j = 0; j < game_objects_count; ++j) {
      systems_[i]->Execute(suffer.GetCurrentScene()->current_gameobjects_[j].get());
    }
  }

  //render_manager_.AddToRenderQueue(std::move(render_system_.get()->dl_));
  render_manager_.AddToRenderQueue(std::move(red_render_system_.get()->dl_));
  render_manager_.AddToRenderQueue(std::move(blue_render_system_.get()->dl_));

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

