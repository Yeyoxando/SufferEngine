#ifndef __AUDIO_COMMANDS_H__
#define __AUDIO_COMMANDS_H__

#include <command.h>
#include <audio.h>
#include <referenced.h>

namespace Suffer {

class AudioCommands : public Referenced {

public:

	AudioCommands();
	~AudioCommands();

	struct Play : public Command {
		Play() {};
		virtual void Execute() override;
		Audio3D* audio_3d_ = nullptr;
		Audio2D* audio_2d_ = nullptr;
	};

	struct Pause : public Command {
		Pause() {};
		virtual void Execute() override;
		Audio3D* audio_3d_ = nullptr;
		Audio2D* audio_2d_ = nullptr;
	};

	struct SetGain : public Command {
		float gain_;
		virtual void Execute() override;
		Audio3D* audio_3d_ = nullptr;
		Audio2D* audio_2d_ = nullptr;
	};


};

}
#endif // __AUDIO_COMMANDS_H__
