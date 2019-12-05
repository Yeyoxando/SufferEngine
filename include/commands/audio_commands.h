/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-10-2019
* AudioCommands Header
*/

#ifndef __AUDIO_COMMANDS_H__
#define __AUDIO_COMMANDS_H__

#include <command.h>
#include <audio.h>
#include <referenced.h>

namespace Suffer {

  namespace AudioCommands {

	    struct Load : public Command {
		    Load() { cmd_type_ = Command::kAudio; }
		    virtual void Execute() const override;
		    char* file;
		    Audio3D* audio_3d_ = nullptr;
	    };

	    struct Play : public Command {
		    Play() { cmd_type_ = Command::kAudio; }
		    virtual void Execute() const override;
		    Audio3D* audio_3d_ = nullptr;
	    };

	    struct Pause : public Command {
		    Pause() { cmd_type_ = Command::kAudio; }
		    virtual void Execute() const override;
		    Audio3D* audio_3d_ = nullptr;
	    };

	    struct SetGain : public Command {
		    SetGain() { cmd_type_ = Command::kAudio; }
		    float gain_;
		    virtual void Execute() const override;
		    Audio3D* audio_3d_ = nullptr;
	    };

      struct Crossfade : public Command {
        Crossfade(Audio3D* from, Audio3D* to, float attenuation);
        Crossfade() {};
        virtual void Execute() const override;
        static Audio3D* from_;
        static Audio3D* to_;
        static void Crossfading();
        static float attenuation_;
        static bool ended_;
      };

  } // End of AudioCommands namespace

} // End of Suffer namespace

#endif // __AUDIO_COMMANDS_H__
