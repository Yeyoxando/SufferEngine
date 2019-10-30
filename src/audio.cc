/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-20-2019
* Audio Source
*/

#include <audio.h>
#include <imgui.h>
#include <interface.h>
#include <soloud.h>
#include <soloud_wav.h>
#include <suffermanager.h>

struct ExampleAppLog {
	void    AddLog(const char* fmt, ...) IM_FMTARGS(2);
};

using namespace Suffer;

// --------------------------------------------------------------//

/*
							   _ _         ___  _____
				/\            | (_)       |__ \|  __ \
			   /  \  _   _  __| |_  ___      ) | |  | |
			  / /\ \| | | |/ _` | |/ _ \    / /| |  | |
			 / ____ \ |_| | (_| | | (_) |  / /_| |__| |
			/_/    \_\__,_|\__,_|_|\___/  |____|_____/

*/

// --------------------------------------------------------------//

struct Audio2D::Data {

	SoLoud::Soloud sound_;
	SoLoud::Wav wave_;
	SoLoud::handle handle_;

};

// --------------------------------------------------------------//

Audio2D::Audio2D(){

	_ptr = new Data();
	_ptr->sound_.init();

}

// --------------------------------------------------------------//

Audio2D::~Audio2D(){

	_ptr->sound_.deinit();
	delete _ptr;

}

// --------------------------------------------------------------//

bool Audio2D::Load(const char* file){

	file_ = file;
	!_ptr->wave_.load(file);
	if(_ptr->wave_.mData != nullptr) return true;
	return false;

}

// --------------------------------------------------------------//

bool Audio2D::Play(){

	_ptr->handle_ = _ptr->sound_.play(_ptr->wave_);
	Interface::log.AddLog("\n[" _information_ "] Reproducing a new 2D song: [%s]", file_);
	if (_ptr->handle_ > 0) return true;
	return false;

}

// --------------------------------------------------------------//

bool Audio2D::Stop(){
	_ptr->sound_.stop(_ptr->handle_);
	return true;
}

// --------------------------------------------------------------//

void Audio2D::SetLooping(const bool looping){
	looping_ = looping;
	_ptr->sound_.setLooping(_ptr->handle_, looping_);
}

// --------------------------------------------------------------//

void Audio2D::SetGain(const double newGain){
	_ptr->wave_.setVolume(newGain);
	gain_ = newGain;
}

// --------------------------------------------------------------//

void Audio2D::SetGlobalVolume(const double newVolume){
	_ptr->sound_.setGlobalVolume(newVolume);
}

// --------------------------------------------------------------//

void Audio2D::SetPitch(const double newPitch){
	_ptr->sound_.setRelativePlaySpeed(_ptr->handle_, newPitch);
	pitch_ = newPitch;
}

// --------------------------------------------------------------//

bool Audio2D::Looping(){
	return looping_;
}

// --------------------------------------------------------------//

double Audio2D::Pitch(){
	return pitch_;
}

// --------------------------------------------------------------//

double Audio2D::Gain(){
	return gain_;
}

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

struct Audio3D::Data {

	SoLoud::Soloud sound_;
	SoLoud::Wav wave_;
	SoLoud::handle handle_;

};

// --------------------------------------------------------------//

Audio3D::Audio3D(){

	_ptr = new Data();
	_ptr->sound_.init();

	gain_ = 1.0f;
	looping_ = false;
	pitch_ = 1.0f;
	hertz_ = 0;

}

// --------------------------------------------------------------//

Audio3D::Audio3D(const Audio3D& copy){
	
	this->file_ = copy.file_;
	this->gain_ = copy.gain_;
	this->hertz_ = copy.hertz_;
	this->pitch_ = copy.pitch_;
	this->looping_ = copy.looping_;

}

// --------------------------------------------------------------//

Audio3D::~Audio3D(){

	_ptr->sound_.deinit();
	if (_ptr == nullptr) return;
	delete _ptr;

}

// --------------------------------------------------------------//

bool Audio3D::Load(const char* file){

	file_ = file;
	_ptr->wave_.load(file);
	if (_ptr->wave_.mData != nullptr) return true;
	return false;

}

// --------------------------------------------------------------//

bool Audio3D::Play3D(glm::vec3 position /*= glm::vec3(0, 0, 0)*/, 
					 glm::vec3 velocity /*= glm::vec3(0, 0, 0)*/){

	_ptr->handle_ = _ptr->sound_.play3d(_ptr->wave_, position.x, position.y, position.z,
										velocity.x, velocity.y, velocity.z);

	Interface::log.AddLog("\n[" _audio_ "] Reproducing a new 3D song: [%s]", file_);

	SetGain(gain_);
	SetPitch(pitch_);
	SetLooping(looping_);

	if (!_ptr->handle_) return false;
	return true;

}

// --------------------------------------------------------------//

void Audio3D::SetGain(const float newGain /*= 1.0f*/){

	gain_ = newGain;
	_ptr->sound_.setVolume(_ptr->handle_, gain_);

}

// --------------------------------------------------------------//

void Audio3D::SetPitch(const float newPitch /*= 1.0f*/){

	pitch_ = newPitch;
	_ptr->sound_.setRelativePlaySpeed(_ptr->handle_, pitch_);

}

// --------------------------------------------------------------//

void Audio3D::SetLooping(const bool looping /*= false*/){

	looping_ = looping;
	_ptr->sound_.setLooping(_ptr->handle_, looping_);

}

// --------------------------------------------------------------//

void Audio3D::SetVelocity(const glm::vec3 newVelocity /*= glm::vec3(0, 0, 0)*/){

}

// --------------------------------------------------------------//

void Audio3D::SetGlobalVolume(const float newVolume /* = 1.0f */) {
	_ptr->sound_.setGlobalVolume(newVolume);
}

// --------------------------------------------------------------//

void Audio3D::SetSoundParameters(glm::vec3 position, glm::vec3 velocity){

	_ptr->sound_.set3dSourceParameters(_ptr->handle_, position.x, position.y, position.z,
									   velocity.x, velocity.y, velocity.z);

}

// --------------------------------------------------------------//

void Audio3D::SetSoundSpeed(glm::vec3 newSpeed){

	_ptr->sound_.set3dSourceVelocity(_ptr->handle_, newSpeed.x, newSpeed.y, newSpeed.z);

}

// --------------------------------------------------------------//

void Audio3D::SetSoundPosition(glm::vec3 newPosition){

	_ptr->sound_.set3dSourcePosition(_ptr->handle_, newPosition.x, newPosition.y, newPosition.z);
	_ptr->sound_.update3dAudio();

}

// --------------------------------------------------------------//

void Audio3D::SetSoundMinMaxDistance(float min, float max){

	_ptr->sound_.set3dSourceMinMaxDistance(_ptr->handle_, min, max);

}

// --------------------------------------------------------------//

void Audio3D::SetSoundAttenuation(u32 attenuation, float rollOffFactor){

	_ptr->sound_.set3dSourceAttenuation(_ptr->handle_, attenuation, rollOffFactor);

}

// --------------------------------------------------------------//

void Audio3D::SetSoundDopplerFactor(float newDopplerFactor){

	_ptr->sound_.set3dSourceDopplerFactor(_ptr->handle_, newDopplerFactor);

}

void Audio3D::SetListenerParameters(glm::vec3 position, glm::vec3 at, glm::vec3 up, glm::vec3 velocity){
	
	_ptr->sound_.set3dListenerParameters(position.x, position.y, position.z, at.x, at.y, at.z,
										 up.x, up.y, up.z, velocity.x, velocity.y, velocity.z);

}

// --------------------------------------------------------------//

void Audio3D::SetListenerPosition(glm::vec3 newPosition){

	_ptr->sound_.set3dListenerPosition(newPosition.x, newPosition.y, newPosition.z);

}

// --------------------------------------------------------------//

void Audio3D::SetListenerAt(glm::vec3 newAt){

	_ptr->sound_.set3dListenerAt(newAt.x, newAt.y, newAt.z);

}

// --------------------------------------------------------------//

void Audio3D::SetListenerUp(glm::vec3 newUp){

	_ptr->sound_.set3dListenerUp(newUp.x, newUp.y, newUp.z);

}

// --------------------------------------------------------------//

void Audio3D::SetListenerVelocity(glm::vec3 newVelocity){

	_ptr->sound_.set3dListenerVelocity(newVelocity.x, newVelocity.y, newVelocity.z);

}

// --------------------------------------------------------------//

int Audio3D::GetHertz(){
	return hertz_;
}

// --------------------------------------------------------------//

double Audio3D::GetGain(){
	return gain_;
}

// --------------------------------------------------------------//

double Audio3D::GetPitch(){
	return pitch_;
}

// --------------------------------------------------------------//

bool Audio3D::GetLooping(){
	return looping_;
}

// --------------------------------------------------------------//

glm::vec3 Audio3D::GetSoundSpeed(){
	return glm::vec3(0, 0, 0);
}

// --------------------------------------------------------------//

bool Audio3D::operator!=(const Audio3D& a){

	return (gain_ != a.gain_		||
			hertz_ != a.hertz_		||
			pitch_ != a.pitch_		||
			looping_ != a.looping_	||
			_ptr->handle_ != a._ptr->handle_);

}

// --------------------------------------------------------------//

void Audio3D::operator=(const Audio3D& a){

	this->Load(a.file_);

	this->gain_    = a.gain_;
	this->hertz_   = a.hertz_;
	this->pitch_   = a.pitch_;
	this->looping_ = a.looping_;

}


// MockupMockupMockupMockupMockupMockupMockupMockupMockupMockupMockupMockup

void Suffer::Audio3D::Execute(){

}

void Suffer::Audio3D::Reproduce(){

}

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