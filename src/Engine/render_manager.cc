#include "render_manager.h"

Suffer::RenderManager::RenderManager(){
	// Empty
}

// --------------------------------------------------------------//

Suffer::RenderManager::~RenderManager(){
	// Empty
}

// --------------------------------------------------------------//

void Suffer::RenderManager::StartUp(){
	// Init here instead of constructor and call in engine init
}

// --------------------------------------------------------------//

void Suffer::RenderManager::ShutDown() {
	// Init here instead of constructor and call in engine finish
}

// --------------------------------------------------------------//

void Suffer::RenderManager::AddToRenderQueue(DisplayList&& logic_dl){
	//	if (!dl_mutex_.try_lock()) {
	//#ifdef DEBUG
	//		printf("\nError trying to lock the render_mutex: [%s]\n", __FUNCTION__);
	//#endif
	//		return;
	//	}
	dl_mutex_.lock();

	// Moves given DL to current DL with std::move
	if (logic_dl.GetDisplayListType() == DisplayList::kDisplayListType_Render) {
		//u32 size = logic_dl.size();
		//for (int i = 0; i < size; ++i) {
		//	render_dl_.dl_commands_.push_back(std::move(logic_dl.dl_commands_[i]));
		//}
		//render_dl_.dl_type_ = logic_dl.dl_type_;
		//logic_dl.dl_commands_.clear();
		list_of_dl_.push_back(std::move(logic_dl));
	}

	dl_mutex_.unlock();
}

// --------------------------------------------------------------//

void Suffer::RenderManager::DoRender(){

	dl_mutex_.lock();

	//u32 size = render_dl_.size();
	//
	//for (int i = 0; i < size; ++i) {
	//	const Command* cmd = render_dl_.dl_commands_[i].get();
	//	cmd->Execute();
	//}
	//
	//render_dl_.clear();

	u32 size = list_of_dl_.front().size();
	
	for (int i = 0; i < size; ++i) {
		const Command* cmd = list_of_dl_.front().dl_commands_[i].get();
		cmd->Execute();
	}
	
	list_of_dl_.pop_front();

	dl_mutex_.unlock();
}

// --------------------------------------------------------------//
