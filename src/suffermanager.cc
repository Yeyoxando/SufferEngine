#include <suffermanager.h>
#include <imgui.h>
#include <scene.h>
#include <input.h>
#include <window.h>
#include "imgui_impl_opengl3.h"
#include <interface.h>
#include <clear.h>
#include <time.h>

struct SufferManager::Data {

	std::vector<EDK3::ref_ptr<Command>> display_list_;
	EDK3::ref_ptr<Scene> scene_;
	Suffer::Window wind_;
	double previous_time_;
	double current_time_;
	double delta_time_;
	Interface interface_;

};

SufferManager::SufferManager(){
	data_ = new Data();

	data_->display_list_ = std::vector<EDK3::ref_ptr<Command>>(0);
	data_->scene_.alloc();
}

void SufferManager::PrepareDraw(){

	EDK3::ref_ptr<Clear> clear_cmd;

	clear_cmd.alloc();
	clear_cmd->SetClearColor(glm::vec4(0.8f));

	AddCommand(clear_cmd.get());

}

SufferManager::~SufferManager(){
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

SufferManager::SufferManager(const SufferManager&){

}

SufferManager& SufferManager::instance() {

	static SufferManager* instance = new SufferManager();
	return *instance;

}

bool SufferManager::Init(){

#ifdef ASSERT
	assert(data_ && "\n Data is null.");
#endif // ASSERT

	data_->wind_.init(800, 600);
	Suffer::InitInput();

	return true;
}

bool SufferManager::Run(){

	while (!Suffer::IsKeyDown(k_Escape)) {

		data_->current_time_ = Suffer::RawTime();
		data_->wind_.processEvents();
		data_->interface_.Update();

		Step(data_->delta_time_);
		
		DrawDisplayList();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		data_->wind_.swapBuffers();

		data_->delta_time_ = (data_->current_time_ - data_->previous_time_) * 0.0001f;
		data_->previous_time_ = data_->current_time_;

	
	}

	return true;
}

bool SufferManager::Step(double time_step){

	PrepareDraw();

	return true;
}

bool SufferManager::Finish(){
	return true;
}

double SufferManager::DeltaTime(){
#ifdef ASSERT
	assert(data_ && "\n Data is null.");
#endif // ASSERT
	return data_->delta_time_;
}

bool SufferManager::ResetDisplayList(){
	if (data_->display_list_.empty()) return true;

	data_->display_list_.clear();
	if (data_->display_list_.empty()) return true;
}

void SufferManager::AddCommand(EDK3::ref_ptr<Command> cmd){
	if (!cmd) return;

	data_->display_list_.push_back(cmd);
}

void SufferManager::DrawDisplayList(){
	for (int i = 0; i < data_->display_list_.size(); ++i){
		Command* cmd = data_->display_list_[i].get();
		cmd->Execute();
	}

	ResetDisplayList();
}
