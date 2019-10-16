#include <suffermanager.h>

#define suffer SufferManager::instance()

// --------------------------------------------------------------//

int main(int argc, char *argv[]) {

	suffer.Init();

	suffer.Run();

	suffer.Finish();

	return 0;

}

// --------------------------------------------------------------//