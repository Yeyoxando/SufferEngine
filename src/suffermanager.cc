#include <suffermanager.h>
#include <imgui.h>

SufferManager::SufferManager(){
	display_list_ = std::vector<EDK3::ref_ptr<Command>>(VECTOR_SIZE);
}

SufferManager::~SufferManager(){

}

SufferManager::SufferManager(const SufferManager&){

}

SufferManager& SufferManager::instance() {

	static SufferManager* instance = new SufferManager();
	return *instance;

}

bool SufferManager::ResetDisplayList(){
	if (display_list_.empty()) return true;

	display_list_.clear();
	if (display_list_.empty()) return true;
}

void SufferManager::AddCommand(EDK3::ref_ptr<Command> cmd){
	if (!cmd) return;

	display_list_.push_back(cmd);
}
