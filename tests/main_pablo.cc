
#include <common_definitions.h>
#if defined _MAIN_PABLO_ && !defined _MAIN_DIEGO_

#include <suffermanager.h>
#include <audio.h>


#define suffer SufferManager::instance()

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

	Audio2D audio_source;
	Audio2D audio_source2;

	audio_source.SetGlobalVolume(3.5f);

	// Source 1
	audio_source.Load("../../../resources/audio/fight!.ogg");
	audio_source.Play();
	audio_source.SetPitch(1.0f);
	audio_source.SetLooping(true);

	// Source 2
	//audio_source2.Load("../../../resources/audio/pressure.ogg");
	//audio_source2.Play();
	//audio_source2.SetPitch(0.97f);
	//audio_source2.SetLooping();

	suffer.Init();

	suffer.Run();

	suffer.Finish();

	return 0;

}

// --------------------------------------------------------------//

#endif