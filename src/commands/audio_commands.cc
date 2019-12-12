/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-10-2019
* AudioCommands Source
*/

#include <audio_commands.h>
#include "thread.h"
#include "ref_ptr.h"
#include "math_utils.h"
#include "common_definitions.h"
#include "suffermanager.h"
#include "internal_audio.h"
#include <assert.h>

Suffer::Audio3D* Suffer::AudioCommands::Crossfade::from_;
Suffer::Audio3D* Suffer::AudioCommands::Crossfade::to_;
float Suffer::AudioCommands::Crossfade::attenuation_;
bool Suffer::AudioCommands::Crossfade::ended_;

// --------------------------------------------------------------//

void Suffer::AudioCommands::Load::Execute() const {

  if (file == nullptr) return;
  if (audio_3d_ == nullptr) return;
  audio_3d_->Load(file);

}

// --------------------------------------------------------------//

void Suffer::AudioCommands::Play::Execute() const {

  if (audio_3d_ == nullptr) return;

  if (audio_3d_->_ptr->handle_ != 0) {
    audio_3d_->_ptr->sound_.stop(audio_3d_->_ptr->handle_);
  }

  audio_3d_->active_ = true;

  mathmorra::Vector3 current_position = audio_3d_->GetSoundPosition();

  audio_3d_->_ptr->handle_ = audio_3d_->_ptr->sound_.play3d(audio_3d_->_ptr->wave_, current_position.x_, current_position.y_, current_position.z_);

  //Interface::log.AddLog("\n[" _audio_ "] Reproducing a new 3D song: [%s]", file_);

  //audio_3d_->SetSoundMinMaxDistance(0.0f, 100.0f);
  audio_3d_->SetSoundAttenuation(2, 1.0f);

  //audio_3d_->SetSoundAttenuation()

  audio_3d_->SetGain(audio_3d_->gain_);
  audio_3d_->SetPitch(audio_3d_->pitch_);
  audio_3d_->SetLooping(audio_3d_->looping_);

}

// --------------------------------------------------------------//

void Suffer::AudioCommands::Pause::Execute() const {

  audio_3d_->_ptr->sound_.setPause(audio_3d_->_ptr->handle_, audio_3d_->paused_);

}

// --------------------------------------------------------------//

void Suffer::AudioCommands::SetGain::Execute() const {

  //if (audio_3d_ == nullptr) return;
  //audio_3d_->SetGain(gain_);

#ifdef ASSERT
  assert(gain_ >= 0 && "¡Volume cannot set under 0!");
#endif

  audio_3d_->gain_ = gain_;
  audio_3d_->_ptr->sound_.setVolume(audio_3d_->_ptr->handle_, gain_);

}

Suffer::AudioCommands::Crossfade::Crossfade(Audio3D* from, Audio3D* to, float attenuation) {
  from_ = from;
  to_ = to;
  cmd_type_ = Command::kAudio;
  attenuation_ = ThiefUtils::Math::Clamp(attenuation, 0.0f, 1.0f);
  ended_ = false;
}

void Suffer::AudioCommands::Crossfade::Execute() const {

#ifdef CUSTOM

  ref_ptr<Thread> coroutine_;
  coroutine_.alloc();

  auto crossfade_job = [] { Crossfading(); };
  coroutine_->NewTask(crossfade_job);

#else

  from_->Fade(0.0f, 2);
  to_->Fade(1.0f, 2);

#endif

}

void Suffer::AudioCommands::Crossfade::Crossfading() {

#ifdef CUSTOM

  suffer.audio_manager_.crossfade_mutex_.lock();
  ended_ = false;

  while (!ended_) {

    float current_from_gain_ = from_->GetGain();
    //current_from_gain_ = ThiefUtils::Math::Lerp(current_from_gain_, 0.0f, attenuation_);
    current_from_gain_ -= attenuation_;
    from_->SetGain(current_from_gain_);

    float current_to_gain_ = to_->GetGain();
    //current_to_gain_ = ThiefUtils::Math::Lerp(current_to_gain_, 1.0f, attenuation_);
    current_to_gain_ += attenuation_;
    to_->SetGain(current_to_gain_);

    if (from_->GetGain() <= 0.01f && to_->GetGain() >= 0.97f) ended_ = true;
    else ended_ = false;

  };

  suffer.audio_manager_.crossfade_mutex_.unlock();

#endif

}
