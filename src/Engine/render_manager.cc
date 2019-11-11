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
	dl_mutex_.lock();

	// Moves given DL to current DL with std::move
	if (logic_dl.GetDisplayListType() == DisplayList::kDisplayListType_Render) {
		list_of_dl_.push_back(std::move(logic_dl));
	}

	dl_mutex_.unlock();
}

// --------------------------------------------------------------//

void Suffer::RenderManager::DoRender(){

	dl_mutex_.lock();

  if (!list_of_dl_.empty()) {
    u32 size = list_of_dl_.front().size();

    for (int i = 0; i < size; ++i) {
      const Command* cmd = list_of_dl_.front().dl_commands_[i].get();
      cmd->Execute();
    }

    list_of_dl_.pop_front();
  }

	dl_mutex_.unlock();

}

// --------------------------------------------------------------//
