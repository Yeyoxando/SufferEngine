
#include <common_definitions.h>
#if defined _MAIN_PABLO_ && !defined _MAIN_DIEGO_

#include <suffermanager.h>
#include <glfw3.h>
#include <px_sched.h>
#include <audio.h>

px_sched::Scheduler schd;
px_sched::Sync thread_logic, thread_render;
bool first_frame = false;


#define suffer SufferManager::instance()

void Render();

void Logic() {
	for (size_t i = 0; i < 10; ++i) {
			printf("Phase 1: Task %zu completed from %s\n",
				i, px_sched::Scheduler::current_thread_name());
	}
	if (!first_frame) first_frame = true;
	else {
		schd.waitFor(thread_render);
		schd.run(Render, &thread_render);
	}

}

void Render() {
	schd.run(Logic, &thread_logic);
	for (size_t i = 0; i < 10; ++i) {
			printf("Phase 2: Task %zu completed from %s\n",
				i, px_sched::Scheduler::current_thread_name());
	}
}

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

#if 0

	Audio2D audio_source;
	Audio2D audio_source2;

	Audio3D audio_source_3d;
	Audio3D audio_source_3d2;

	audio_source_3d.SetGlobalVolume(1.5f);

// 0: Audio2D
// 1: Audio3D
#if 1

	glm::vec3 position, velocity, listener_position;
	position = glm::vec3(1.0f, 0.0f, 0.0f);
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	listener_position = glm::vec3(0.0f, 0.0f, -0.5f);

#if 1 // ONLY ONE RESOURCE AT LEFT
	
	// 3D Source 1
	audio_source_3d.Load("../../../resources/audio/fight_mono.ogg");
	audio_source_3d.SetLooping(true);
	audio_source_3d.SetPitch(1.0f);
	audio_source_3d.SetGain(1.0f);
	audio_source_3d.Play3D(position, velocity);
	audio_source_3d.SetListenerPosition(listener_position);	

	//position = glm::vec3(1.0f, 0.0f, 0.0f);
	//audio_source_3d2.Load("../../../resources/audio/pressure.ogg");
	//audio_source_3d2.Play3D(glm::vec3(-1.0f, 0.0f, 0.0f), velocity);


	//float position2[3] = { 1.0f, 0.0f, 0.0f };
	//while (1) {
	//	position2[0] -= 0.0000005f;
	//	audio_source_3d.SetSoundPosition(glm::vec3(position2[0], position2[1], position2[2]));
	//	//audio_source_3d2.SetSoundPosition(glm::vec3(-position2[0], position2[1], position2[2]));
	//	if (position2[0] < -1.0f) {
	//		position2[0] = 1.0f;
	//	}
	//}
	
#endif

	// 3D Source 2


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

#endif


	schd.init();




	// manually increment the sync object, to control any task that will be
	// attached to it. Tasks are executed when sync objects reach zero.
	//schd.incrementSync(&s1);

	printf("\n");

	schd.run(Logic, &thread_logic);
	schd.runAfter(thread_logic, Render, &thread_render);


	while (1) {
	
	}

	suffer.Init();

	suffer.Run();

	suffer.Finish();

	return 0;

}
 
// --------------------------------------------------------------//

#endif