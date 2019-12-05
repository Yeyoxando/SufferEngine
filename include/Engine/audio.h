/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-20-2019
* Audio Header
*/

#include "vector3.h"
#include <command.h>
#include <data_types.h>
#include "audio_commands.h"
#include "component.h"

#ifndef __AUDIO_H__
#define __AUDIO_H__

namespace Suffer {

  namespace AudioCommands {
    class Play;
  }

  // ---------------------------------------------------------------------- //

  class Audio3D : public Component {
    friend class Suffer::AudioCommands::Play;
    public:
      Audio3D();
      Audio3D(const Audio3D& copy);

      /**
       * @brief: loads an audio file.
       * @param: the path of the file in the explorer.
       */
      bool Load(char* file);

      // Plays the audio source
      bool Play3D(mathmorra::Vector3 velocity = mathmorra::Vector3(0, 0, 0));

      void Fade(float volume, float time);

      void SetPaused(const bool paused);
      void SetGain(const float newGain = 1.0f);
      void SetPitch(const float newPitch = 1.0f); // a.k.a reproduce speed
      void SetLooping(const bool looping = false);

      // Sets the velocity of the audio source, not his reproduce speed.
      void SetVelocity(const mathmorra::Vector3 newVelocity = mathmorra::Vector3(0, 0, 0));
      void SetGlobalVolume(const float newVolume = 1.0f);

      // Sound
      void SetSoundParameters(mathmorra::Vector3 position, mathmorra::Vector3 velocity);
      void SetSoundSpeed(mathmorra::Vector3 newSpeed);
      void SetSoundPosition(mathmorra::Vector3 newPosition);
      void SetSoundMinMaxDistance(float min, float max);
      void SetSoundAttenuation(u8 attenuation, float rollOffFactor);
      void SetSoundDopplerFactor(float newDopplerFactor);
      void SetMonotoneParams(u32 channels, u32 wave_form);

      // Listener
      void SetListenerParameters(mathmorra::Vector3 position, mathmorra::Vector3 at, mathmorra::Vector3 up, mathmorra::Vector3 velocity);
      static void SetListenerPosition(mathmorra::Vector3 newPosition);
      static void SetListenerAt(mathmorra::Vector3 newAt);
      static void SetListenerUp(mathmorra::Vector3 newUp);
      static void SetListenerVelocity(mathmorra::Vector3 newVelocity);

      // Getters
      bool isPaused();
      u32 GetHertz();
      double GetGain();
      double GetPitch();
      bool GetLooping();
      float* Wave();
      float* FFT(); // FFT: Fast Fourier Transform

      mathmorra::Vector3 GetSoundPosition();
      mathmorra::Vector3 GetSoundSpeed();

      // Operand overload
      void operator=(const Audio3D& a);
      bool operator!=(const Audio3D& a);

    protected:
      ~Audio3D();

    private:

      u32    hertz_;
      bool   looping_;
      double pitch_;
      double gain_;
      char* file_;
      bool paused_;

      mathmorra::Vector3 current_position_;
      mathmorra::Vector3 current_velocity_;

      struct Data;
      Data* _ptr = nullptr;

    };

    // ---------------------------------------------------------------------- //
  } // End of Suffer namespace

#endif  // __AUDIO_H__
