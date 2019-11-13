
#include <audio_commands.h>

// --------------------------------------------------------------//

void Suffer::AudioCommands::Load::Execute() const {

	if (file == nullptr) return;
	if (audio_3d_ == nullptr) return;
	audio_3d_->Load(file);

}

// --------------------------------------------------------------//

void Suffer::AudioCommands::Play::Execute() const {

	if (audio_3d_ == nullptr) return;
	audio_3d_->Play3D();

}

// --------------------------------------------------------------//

void Suffer::AudioCommands::Pause::Execute() const {

	if (audio_3d_ == nullptr) return;
	audio_3d_->SetPaused(true);

}

// --------------------------------------------------------------//

void Suffer::AudioCommands::SetGain::Execute() const {

	if (audio_3d_ == nullptr) return;
	audio_3d_->SetGain(gain_);

}

