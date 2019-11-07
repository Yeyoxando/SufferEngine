// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __SUFFER_MANAGER_H__
#define __SUFFER_MANAGER_H__

#include <game_object.h>
#include <geometry.h>
#include <material.h>
#include <ref_ptr.h>
#include <scene.h>
#include <audio.h>
#include <render_manager.h>

//Hide from here
#include <display_list.h>
#include <command.h>
#include <thread.h>

// --------------------------------------------------------------//

class SufferManager {

public:
	static SufferManager& instance();

	friend class Audio3D;
	friend class Audio2D;
	friend class Interface;

	bool Init();
	bool Run();
	bool Step(double time_step);
	bool Finish();

	double DeltaTime();

	void SetPredefiniedShape(ref_ptr <Geometry> geo, Geometry::BasicShapes shape);
	void SetPredefiniedMaterial(ref_ptr <Material> mat, Material::BasicMaterials basic_mat);


	Audio3D newSong;

	// Subsystems
	RenderManager render_manager_;

protected:

	SufferManager();
	virtual ~SufferManager();

private:

	SufferManager(const SufferManager&);

	struct Data;
	Data* data_;

	void Input();
	void Update();
	void Draw();

	// Threads
	ref_ptr<Thread> logic_;
	ref_ptr<Thread> input_;
	ref_ptr<Thread> audio_;

	// Audio STUFF
	std::vector<ref_ptr<Command>> audio_dl_;

	// DisplayLists Stuff
	void Audio();
	void PrepareAudio();


};

// --------------------------------------------------------------//


#endif // __SUFFER_MANAGER_H__
