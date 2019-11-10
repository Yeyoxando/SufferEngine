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

};

}
#endif // __AUDIO_COMMANDS_H__
