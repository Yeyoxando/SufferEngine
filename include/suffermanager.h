// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __SUFFER_MANAGER_H__
#define __SUFFER_MANAGER_H__

#include <vector>
#include <ref_ptr.h>

//Hide from here
#include <GL/glew.h>
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

	// HELLO TRIANGLE STUFF
	GLuint triangle_vertices_ID;
	GLuint triangle_indices_ID;
	GLuint vertex_shader_ID;
	GLuint fragment_shader_ID;
	GLuint program_ID;

protected:

	SufferManager();
	virtual ~SufferManager();

private:
	SufferManager(const SufferManager&);

	void PrepareDraw();
	void DrawDisplayList();
	bool ResetDisplayList();

	struct Data;
	Data* data_;
};

// --------------------------------------------------------------//


#endif // __SUFFER_MANAGER_H__
