#include <suffermanager.h>
#include <imgui.h>

SufferManager::SufferManager(){
	   
}

SufferManager::~SufferManager(){

}

SufferManager::SufferManager(const SufferManager&){

}

SufferManager& SufferManager::instance() {

	static SufferManager* instance = new SufferManager();
	return *instance;

}