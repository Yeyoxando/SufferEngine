#include "audio_manager.h"
#include "audio_commands.h"
#include "suffermanager.h"
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
    u32 size = audio_dl_by_logic_.Size();
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

	u32 size = audio_dl_.Size();
	
	for (u32 i = 0; i < size; ++i) {
		const Command* cmd = audio_dl_.dl_commands_[i].get();
    if(cmd != nullptr)
		  cmd->Execute();
	}
	
  audio_dl_.Clear();

	dl_mutex_.unlock();

}

// --------------------------------------------------------------//
