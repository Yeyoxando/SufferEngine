/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-20-2019
* Audio Source
*/

#include <audio.h>
#include <imgui.h>
#include <interface.h>
#include <soloud.h>
#include <soloud_monotone.h>
#include <soloud_wav.h>
#include <suffermanager.h>
#include <audio_manager.h>

struct ExampleAppLog {
	void    AddLog(const char* fmt, ...) IM_FMTARGS(2);
};

// --------------------------------------------------------------//

/*
                       _ _         ____  _____
        /\            | (_)       |___ \|  __ \
       /  \  _   _  __| |_  ___     __) | |  | |
      / /\ \| | | |/ _` | |/ _ \   |__ <| |  | |
     / ____ \ |_| | (_| | | (_) |  ___) | |__| |
    /_/    \_\__,_|\__,_|_|\___/  |____/|_____/

*/

// --------------------------------------------------------------//

struct Suffer::Audio3D::Data {

	SoLoud::Soloud sound_;
	SoLoud::Wav wave_;
	SoLoud::handle handle_;
	SoLoud::Monotone wave_form_;

};

// --------------------------------------------------------------//

Suffer::Audio3D::Audio3D(){

#ifdef ASSERT
    assert(SufferManager::instance().audio_manager_.audio_sources_ <
        SufferManager::instance().audio_manager_.max_audio_sources_
        && "Too many audio sources!");
#endif

    SufferManager::instance().audio_manager_.audio_sources_++;
    _ptr = new Data();
    _ptr->sound_.init(SoLoud::Soloud::ENABLE_VISUALIZATION);
    
    gain_ = 1.0f;
    looping_ = false;
    pitch_ = 1.0f;
    hertz_ = 0;
    paused_ = false;
    
    current_position_ = mathmorra::Vector3(0, 0, 0);
    current_velocity_ = mathmorra::Vector3(0, 0, 0);

    suffer.audio_manager_.audio_container_.push_back(this);

}

// --------------------------------------------------------------//

Suffer::Audio3D::Audio3D(const Audio3D& copy){
	
	this->file_ = copy.file_;
	this->gain_ = copy.gain_;
	this->hertz_ = copy.hertz_;
	this->pitch_ = copy.pitch_;
	this->looping_ = copy.looping_;

}

// --------------------------------------------------------------//

Suffer::Audio3D::~Audio3D(){

	_ptr->sound_.deinit();
	if (_ptr == nullptr) return;
	delete _ptr;

}

// --------------------------------------------------------------//

bool Suffer::Audio3D::Load(char* file){

	file_ = file;
	_ptr->wave_.load(file);
	if (_ptr->wave_.mData != nullptr) return true;

	Interface::log.AddLog("\n[" _error_ "] File not found!: [%s]", file_);
	return false;

}

// --------------------------------------------------------------//

bool Suffer::Audio3D::Play3D(mathmorra::Vector3 velocity /*= mathmorra::Vector3(0, 0, 0)*/){

	if (_ptr->handle_ != 0) {
		_ptr->sound_.stop(_ptr->handle_);
	}

	mathmorra::Vector3 current_position = GetSoundPosition();

	_ptr->handle_ = _ptr->sound_.play3d(_ptr->wave_, current_position.x_, current_position.y_, current_position.z_,
										velocity.x_, velocity.y_, velocity.z_);

	if (_ptr->wave_.mData == nullptr) return false;
	Interface::log.AddLog("\n[" _audio_ "] Reproducing a new 3D song: [%s]", file_);

  SetSoundMinMaxDistance(0.0f, 10000.0f);
  SetSoundAttenuation(2, 1.0f);

	SetGain(gain_);
	SetPitch(pitch_);
	SetLooping(looping_);

	SetPaused(false);

	if (!_ptr->handle_) return false;
	return true;

}

// --------------------------------------------------------------//

void Suffer::Audio3D::Fade(float volume, float time){
  _ptr->sound_.fadeVolume(_ptr->handle_, volume, time);
}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetGain(const float newGain /*= 1.0f*/){

#ifdef ASSERT
	assert(newGain >= 0 && "¡Volume cannot set under 0!");
#endif
	gain_ = newGain;
	_ptr->sound_.setVolume(_ptr->handle_, gain_);

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetPitch(const float newPitch /*= 1.0f*/) {

	pitch_ = newPitch;
	_ptr->sound_.setRelativePlaySpeed(_ptr->handle_, pitch_);

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetLooping(const bool looping /*= false*/){

	looping_ = looping;
	_ptr->sound_.setLooping(_ptr->handle_, looping_);

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetVelocity(const mathmorra::Vector3 newVelocity /*= mathmorra::Vector3(0, 0, 0)*/){

	_ptr->sound_.set3dSourceVelocity(_ptr->handle_, newVelocity.x_, newVelocity.y_, newVelocity.z_);
	_ptr->sound_.update3dAudio();
	current_velocity_ = newVelocity;

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetGlobalVolume(const float newVolume /* = 1.0f */) {
	_ptr->sound_.setGlobalVolume(newVolume);
}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetSoundParameters(mathmorra::Vector3 position, mathmorra::Vector3 velocity){

	_ptr->sound_.set3dSourceParameters(_ptr->handle_, position.x_, position.y_, position.z_,
									   velocity.x_, velocity.y_, velocity.z_);

	current_position_ = position;
	current_velocity_ = velocity;

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetSoundSpeed(mathmorra::Vector3 newSpeed){

	_ptr->sound_.set3dSourceVelocity(_ptr->handle_, newSpeed.x_, newSpeed.y_, newSpeed.z_);

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetSoundPosition(mathmorra::Vector3 newPosition){

	_ptr->sound_.set3dSourcePosition(_ptr->handle_, newPosition.x_, newPosition.y_, newPosition.z_);
	_ptr->sound_.update3dAudio();
	current_position_ = newPosition;

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetSoundMinMaxDistance(float min, float max){

	_ptr->sound_.set3dSourceMinMaxDistance(_ptr->handle_, min, max);
	_ptr->sound_.update3dAudio();

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetSoundAttenuation(u8 attenuation, float rollOffFactor){

	_ptr->sound_.set3dSourceAttenuation(_ptr->handle_, attenuation, rollOffFactor);

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetSoundDopplerFactor(float newDopplerFactor){

	_ptr->sound_.set3dSourceDopplerFactor(_ptr->handle_, newDopplerFactor);

}

void Suffer::Audio3D::SetListenerParameters(mathmorra::Vector3 position, mathmorra::Vector3 at, mathmorra::Vector3 up, mathmorra::Vector3 velocity){
	
	_ptr->sound_.set3dListenerParameters(position.x_, position.y_, position.z_, at.x_, at.y_, at.z_,
										 up.x_, up.y_, up.z_, velocity.x_, velocity.y_, velocity.z_);
  _ptr->sound_.update3dAudio();

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetListenerPosition(mathmorra::Vector3 newPosition){

  SoLoud::Soloud sound_;
	sound_.set3dListenerPosition(newPosition.x_, newPosition.y_, newPosition.z_);
	sound_.update3dAudio();

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetListenerAt(mathmorra::Vector3 newAt){
  
  SoLoud::Soloud sound_;
	sound_.set3dListenerAt(newAt.x_, newAt.y_, newAt.z_);

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetListenerUp(mathmorra::Vector3 newUp){

  SoLoud::Soloud sound_;
	sound_.set3dListenerUp(newUp.x_, newUp.y_, newUp.z_);

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetListenerVelocity(mathmorra::Vector3 newVelocity){

  SoLoud::Soloud sound_;
	sound_.set3dListenerVelocity(newVelocity.x_, newVelocity.y_, newVelocity.z_);

}

// --------------------------------------------------------------//

u32 Suffer::Audio3D::GetHertz(){
	return hertz_;
}

// --------------------------------------------------------------//

double Suffer::Audio3D::GetGain(){
	return gain_;
}

// --------------------------------------------------------------//

double Suffer::Audio3D::GetPitch(){
	return pitch_;
}

// --------------------------------------------------------------//

bool Suffer::Audio3D::GetLooping(){
	return looping_;
}

// --------------------------------------------------------------//

mathmorra::Vector3 Suffer::Audio3D::GetSoundSpeed(){
	return mathmorra::Vector3(0, 0, 0);
}

// --------------------------------------------------------------//

bool Suffer::Audio3D::operator!=(const Audio3D& a){

	return (gain_ != a.gain_		||
			hertz_ != a.hertz_		||
			pitch_ != a.pitch_		||
			looping_ != a.looping_	||
			_ptr->handle_ != a._ptr->handle_);

}

// --------------------------------------------------------------//

void Suffer::Audio3D::operator=(const Audio3D& a){

	this->Load(a.file_);

	this->gain_    = a.gain_;
	this->hertz_   = a.hertz_;
	this->pitch_   = a.pitch_;
	this->looping_ = a.looping_;

}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetPaused(const bool paused){
	paused_ = paused;
	_ptr->sound_.setPause(_ptr->handle_, paused_);
}

// --------------------------------------------------------------//

void Suffer::Audio3D::SetMonotoneParams(u32 channels, u32 wave_form){
	_ptr->wave_form_.setParams(channels, wave_form);
}

// --------------------------------------------------------------//

bool Suffer::Audio3D::isPaused(){
	return paused_;
}

// --------------------------------------------------------------//

float* Suffer::Audio3D::Wave(){

	float* wave = _ptr->sound_.getWave();
	return wave;

}

// --------------------------------------------------------------//

float* Suffer::Audio3D::FFT(){
	return _ptr->sound_.calcFFT();
}

// --------------------------------------------------------------//

mathmorra::Vector3 Suffer::Audio3D::GetSoundPosition(){
	return current_position_;
}

// MockupMockupMockupMockupMockupMockupMockupMockupMockupMockupMockupMockup

//void Suffer::Audio3D::Execute(){
//	Play3D();
//}
//
//void Suffer::Audio3D::Reproduce(){
//
//}

// MockupMockupMockupMockupMockupMockupMockupMockupMockupMockupMockupMockup

// --------------------------------------------------------------//

//Audio3D Audio3D::operator=(const Audio3D& a) const{
//
//	Audio3D newSource;
//
//	newSource.Load(a.file_);
//
//	newSource.gain_    = a.gain_;
//	newSource.hertz_   = a.hertz_;
//	newSource.pitch_   = a.pitch_;
//	newSource.looping_ = a.looping_;
//
//	return newSource;
//
//}

// --------------------------------------------------------------//