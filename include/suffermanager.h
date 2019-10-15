// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __SUFFER_MANAGER_H__
#define __SUFFER_MANAGER_H__

#include <vector>
#include <ref_ptr.h>
#include <command.h>

#define VECTOR_SIZE 128

class SufferManager {

public:
	static SufferManager& instance();

	bool ResetDisplayList();
	void AddCommand(EDK3::ref_ptr<Command> cmd);

protected:

	SufferManager();
	virtual ~SufferManager();

private:
	SufferManager(const SufferManager&);

	std::vector<EDK3::ref_ptr<Command>> display_list_;

};


#endif // __SUFFER_MANAGER_H__
