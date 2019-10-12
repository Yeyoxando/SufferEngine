#include <gpumanager.h>

Suffer::GPUManager::GPUManager(){
	   
}

Suffer::GPUManager::~GPUManager(){

}

Suffer::GPUManager::GPUManager(const GPUManager&){

}

Suffer::GPUManager& Suffer::GPUManager::instance() {

	static GPUManager* instance = new GPUManager();
	return *instance;

}