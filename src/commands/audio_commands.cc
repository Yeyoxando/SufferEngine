
#include <audio_commands.h>

void Suffer::AudioCommands::Play::Execute(){

	if (audio_3d_ == nullptr) return;
	audio_3d_->SetPaused(false);

}

void Suffer::AudioCommands::Pause::Execute(){

	if (audio_3d_ == nullptr) return;
	audio_3d_->SetPaused(true);

}

void Suffer::AudioCommands::SetGain::Execute(){

	if (audio_3d_ == nullptr) return;
	audio_3d_->SetGain(gain_);

}

Suffer::AudioCommands::AudioCommands(){

}

Suffer::AudioCommands::~AudioCommands(){

}
