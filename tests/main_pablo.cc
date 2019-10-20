
#include <common_definitions.h>
#if defined _MAIN_PABLO_ && !defined _MAIN_DIEGO_

#include <suffermanager.h>
#include <audio.h>


#define suffer SufferManager::instance()

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

	Audio2D audio_source;
	Audio2D audio_source2;

	Audio3D audio_source_3d;
	Audio3D audio_source_3d2;

	audio_source_3d.SetGlobalVolume(1.5f);

// 0: Audio2D
// 1: Audio3D
#if 1

	glm::vec3 position, velocity, listener_position;
	position = glm::vec3(-1.0f, 0.0f, 0.0f);
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	listener_position = glm::vec3(0.0f, 0.0f, 0.0f);

	// 3D Source 1
	audio_source_3d.Load("../../../resources/audio/fight_mono.ogg");
	audio_source_3d.Play3D(position, velocity);
	audio_source_3d.SetListenerPosition(listener_position);	
	
#if 0 // ONLY ONE RESOURCE AT LEFT

	// 3D Source 2
	position = glm::vec3(1.0f, 0.0f, 0.0f);
	audio_source_3d2.Load("../../../resources/audio/pressure.ogg");
	audio_source_3d2.Play3D(position, velocity);

#endif


#else

	// Source 1
	audio_source.Load("../../../resources/audio/fight!.ogg");
	audio_source.Play();
	audio_source.SetPitch(1.0f);
	audio_source.SetLooping(true);

	// Source 2
	audio_source2.Load("../../../resources/audio/pressure.ogg");
	audio_source2.Play();
	audio_source2.SetPitch(0.97f);
	audio_source2.SetLooping();

#endif

	suffer.Init();

	suffer.Run();

	suffer.Finish();

	return 0;

}

// --------------------------------------------------------------//

#endif