/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-20-2019
* Audio Source
*/

#include <audio.h>
#include <soloud.h>
#include <soloud_wav.h>

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

	!_ptr->wave_.load(file);
	if(_ptr->wave_.mData != nullptr) return true;
	return false;

}

// --------------------------------------------------------------//

bool Audio2D::Play(){

	_ptr->handle_ = _ptr->sound_.play(_ptr->wave_);
	return true;

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
}

// --------------------------------------------------------------//

Audio3D::~Audio3D(){
	delete _ptr;
}

// --------------------------------------------------------------//

bool Audio3D::Load(const char* file){
	return false;
}

// --------------------------------------------------------------//

bool Audio3D::Play3D(glm::vec3 position, glm::vec3 velocity){
	return false;
}

// --------------------------------------------------------------//

void Audio3D::SetPitch(const float newPitch /*= 1.0f*/){

}

// --------------------------------------------------------------//

void Audio3D::SetLooping(const bool looping /*= false*/){

}

// --------------------------------------------------------------//

void Audio3D::SetVelocity(const glm::vec3 newVelocity /*= glm::vec3(0, 0, 0)*/){

}

// --------------------------------------------------------------//