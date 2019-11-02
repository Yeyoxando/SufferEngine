/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-02-2019
* DisplayLists Header
* Base structure extracted from px_render.h (Pplux)
*/

#ifndef __DISPLAY_LIST_H__
#define __DISPLAY_LIST_H__

#include <referenced.h>
#include <audio.h>

namespace Suffer {

class DisplayList : public Referenced {

public:

	// Constructors
	DisplayList();
	~DisplayList();
	
	// Copy-Constructors
	DisplayList(const DisplayList&) = delete;
	DisplayList(DisplayList&& d);

	struct ClearCommands {
		ClearCommands() {};
		void Clear();
	};

	struct AudioCommands {
		AudioCommands() {};
		void Play(Audio3D* source);
		void Load(Audio3D* source, char* file);
		void SetGain(Audio3D* source, const float newGain);
	};

	AudioCommands& audioCommand();
	ClearCommands& clearCommand();

	// DL Functions
	void reset();

	DisplayList clone() const;
	bool clone(DisplayList& out);

	void addCommand(const AudioCommands &command) { audioCommand() = command; }
	void addCommand(const ClearCommands &command) { clearCommand() = command; }

	enum CommandType {
		kClear = 0,
		kAudio = 1,
		kNONE = 20 // MAX for enum.
	};


	struct Command;
	struct Data;
	Data* data_ = nullptr;

};

}
#endif // __DISPLAY_LIST_H__
