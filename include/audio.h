/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-20-2019
* Audio2D Header
*/

#include <glm.hpp>
#include <data_types.h>

#ifndef __AUDIO_H__
#define __AUDIO_H__

// ---------------------------------------------------------------------- //

class Audio2D {

public:

	Audio2D();
	~Audio2D();

	bool Load(const char* file);
	bool Play();
	bool Stop();

	// Setters
	void SetGain(const double newGain = 1.0f); // Gain (a.k.a volume)
	void SetPitch(const double newPitch = 1.0f);
	void SetLooping(const bool looping = false);
	void SetGlobalVolume(const double newVolume = 1.0f);

	// Getters
	double Gain();
	double Pitch();
	bool   Looping();

private:

	int    hertz_;
	bool   looping_;
	double pitch_;
	double gain_;

	struct Data;
	Data* _ptr;

};

// ---------------------------------------------------------------------- //

class Audio3D {

public:

	Audio3D();
	~Audio3D();

	bool Load(const char* file);
	bool Play3D(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 velocity = glm::vec3(0, 0, 0));

	void SetGain(const float newGain = 1.0f);
	void SetPitch(const float newPitch = 1.0f);
	void SetLooping(const bool looping = false);
	void SetVelocity(const glm::vec3 newVelocity = glm::vec3(0, 0, 0));
	void SetGlobalVolume(const float newVolume = 1.0f);

	// Sound
	void SetSoundParameters(glm::vec3 position, glm::vec3 velocity);
		void SetSoundSpeed(glm::vec3 newSpeed);
		void SetSoundPosition(glm::vec3 newPosition);
		void SetSoundMinMaxDistance(float min, float max);
		void SetSoundAttenuation(u32 attenuation, float rollOffFactor);
		void SetSoundDopplerFactor(float newDopplerFactor);
	
	// Listener
	void SetListenerParameters(glm::vec3 position, glm::vec3 at, glm::vec3 up, glm::vec3 velocity);
		void SetListenerPosition(glm::vec3 newPosition);
		void SetListenerAt(glm::vec3 newAt);
		void SetListenerUp(glm::vec3 newUp);
		void SetListenerVelocity(glm::vec3 newVelocity);

private:

	int    hertz_;
	bool   looping_;
	double pitch_;
	double gain_;

	struct Data;
	Data* _ptr;

};

// ---------------------------------------------------------------------- //

#endif  // __AUDIO_H__
