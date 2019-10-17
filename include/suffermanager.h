// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __SUFFER_MANAGER_H__
#define __SUFFER_MANAGER_H__

#include <vector>
#include <ref_ptr.h>

//Hide from here
#include <command.h>

// --------------------------------------------------------------//

class SufferManager {

public:
	static SufferManager& instance();

	bool Init();
	bool Run();
	bool Step(double time_step);
	bool Finish();

	double DeltaTime();
	void AddCommand(EDK3::ref_ptr<Command> cmd);

protected:

	SufferManager();
	virtual ~SufferManager();

private:
	SufferManager(const SufferManager&);

	void PrepareDraw();
	void DrawDisplayList();
	bool ResetDisplayList();

	struct Data;
	Data* data_ = nullptr;
};

// --------------------------------------------------------------//


#endif // __SUFFER_MANAGER_H__
