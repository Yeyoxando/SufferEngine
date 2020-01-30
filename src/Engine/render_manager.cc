// Diego Ochando Torres <ochandoto@esat-alumni.com>

#include "render_manager.h"

// ------------------------------------------------------------------------- //

Suffer::RenderManager::RenderManager(){

	// Empty

}

// ------------------------------------------------------------------------- //

Suffer::RenderManager::~RenderManager(){

	// Empty

}

// ------------------------------------------------------------------------- //

void Suffer::RenderManager::StartUp(){

	// Init here instead of constructor and call in engine init
  dls_to_draw_ = 0;

}

// ------------------------------------------------------------------------- //

void Suffer::RenderManager::ShutDown() {

	// Init here instead of constructor and call in engine finish

}

// ------------------------------------------------------------------------- //

void Suffer::RenderManager::AddToRenderQueue(DisplayList&& logic_dl){

	dl_mutex_.lock();

	// Moves given DL to current DL with std::move
	if (logic_dl.GetDisplayListType() == DisplayList::kDisplayListType_Render) {
    list_of_dl_.push_back(std::move(logic_dl));
    dls_to_draw_++;
	}

	dl_mutex_.unlock();

}

// ------------------------------------------------------------------------- //

void Suffer::RenderManager::DoRender(){
  
  u32 render_buckets = dls_to_draw_;

  // Extract first DisplayList of the list
  for (u32 i = 0; i < render_buckets; ++i) {
    dl_mutex_.lock();

    if (!list_of_dl_.empty())
      render_dl_ = std::move(list_of_dl_.front());

    list_of_dl_.pop_front();

    dls_to_draw_--;

    dl_mutex_.unlock();


    // Execute the extracted DL
    u32 size = render_dl_.Size();

    for (int i = 0; i < size; ++i) {
      const Command* cmd = render_dl_.dl_commands_[i].get();
      cmd->Execute();
    }

    render_dl_.Clear();

  }

}

// ------------------------------------------------------------------------- //
