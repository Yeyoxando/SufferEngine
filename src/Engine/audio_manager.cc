#include "audio_manager.h"
#include "common_definitions.h"

Suffer::AudioManager::AudioManager() {
    // Empty
}

// --------------------------------------------------------------//

Suffer::AudioManager::~AudioManager() {
    // Empty
}

// --------------------------------------------------------------//

void Suffer::AudioManager::StartUp() {

    audio_container_ = std::vector<ref_ptr<Audio3D>>(0);
    max_audio_sources_ = MAX_AUDIO_SOURCES;
    audio_sources_ = 0;

}

// --------------------------------------------------------------//

void Suffer::AudioManager::ShutDown() {
    // Init here instead of constructor and call in engine finish
}

// --------------------------------------------------------------//

void Suffer::AudioManager::AddToAudioQueue(DisplayList&& audio_dl_by_logic_){

    dl_mutex_.lock();

	// Moves given DL to current DL with std::move
	if (audio_dl_by_logic_.GetDisplayListType() == DisplayList::kDisplayListType_Audio) {
    u32 size = audio_dl_by_logic_.size();
    for (u32 i = 0; i < size; ++i) {
        audio_dl_.dl_commands_.push_back(std::move(audio_dl_by_logic_.dl_commands_[i]));
    }
    audio_dl_.dl_type_ = audio_dl_by_logic_.dl_type_;
    audio_dl_by_logic_.dl_commands_.clear();
	}

	dl_mutex_.unlock();

}

// --------------------------------------------------------------//

void Suffer::AudioManager::DoAudio(){

	dl_mutex_.lock();

	u32 size = audio_dl_.size();
	
	for (u32 i = 0; i < size; ++i) {
		const Command* cmd = audio_dl_.dl_commands_[i].get();
		cmd->Execute();
	}
	
  audio_dl_.clear();

	dl_mutex_.unlock();

}

// --------------------------------------------------------------//
