
#include <common_definitions.h>
#if !defined _MAIN_PABLO_ && !defined _MAIN_DIEGO_

#include <suffermanager.h>
#include <glfw3.h>
#include <audio.h>
#include "chrono.h"
#include "ref_ptr.h"
#include "audio_commands.h"
#include "audio.h"

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

	suffer.Init();

	suffer.Run();

	suffer.Finish();

	return 0;

}
 
// --------------------------------------------------------------//

#endif