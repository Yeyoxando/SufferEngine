/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-20-2019
* Audio Header
*/

#include <glm.hpp>
#include <command.h>
#include <data_types.h>

#ifndef __AUDIO_H__
#define __AUDIO_H__

namespace Suffer {

// ---------------------------------------------------------------------- //

	class Audio2D : public Command {

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
		float* Wave();
		float* FFT();

		virtual void Execute() override;

	private:

		int    hertz_;
		bool   looping_;
		double pitch_;
		double gain_;
		const char* file_;

		struct Data;
		Data* _ptr;

	};

// ---------------------------------------------------------------------- //

	class Audio3D : public Command {

	public:

		Audio3D();
		~Audio3D();
		Audio3D(const Audio3D& copy);

		bool Load(char* file);
		bool Play3D(glm::vec3 velocity = glm::vec3(0, 0, 0));

		void SetPaused(const bool paused);
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
		void SetMonotoneParams(int channels, int wave_form);

		// Listener
		void SetListenerParameters(glm::vec3 position, glm::vec3 at, glm::vec3 up, glm::vec3 velocity);
		void SetListenerPosition(glm::vec3 newPosition);
		void SetListenerAt(glm::vec3 newAt);
		void SetListenerUp(glm::vec3 newUp);
		void SetListenerVelocity(glm::vec3 newVelocity);

		// Getters
		bool isPaused();
		int GetHertz();
		double GetGain();
		double GetPitch();
		bool GetLooping();
		float* Wave();
		float* FFT(); // FFT: Fast Fourier Transform

		glm::vec3 GetSoundPosition();
		glm::vec3 GetSoundSpeed();

		// Operand overload
		void operator=(const Audio3D& a);
		//Audio3D operator=(const Audio3D& a) const;

		bool operator!=(const Audio3D& a);

		// Commands Stuff -- Mockup
		virtual void Execute() override;
		virtual void Reproduce();

	private:

		int    hertz_;
		bool   looping_;
		double pitch_;
		double gain_;
		char* file_;
		bool paused_;

		glm::vec3 current_position_;
		glm::vec3 current_velocity_;

		struct Data;
		Data* _ptr = nullptr;

	};

	// ---------------------------------------------------------------------- //
} // End of Suffer namespace

#endif  // __AUDIO_H__
