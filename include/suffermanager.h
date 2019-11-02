// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __SUFFER_MANAGER_H__
#define __SUFFER_MANAGER_H__

#include <vector>
#include <game_object.h>
#include <geometry.h>
#include <material.h>
#include <ref_ptr.h>
#include <scene.h>
#include <mutex>
#include <audio.h>

//Hide from here
#include <display_list.h>
#include <command.h>
#include <thread.h>

// SCHEDULER

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
	void AddCommand(EDK3::ref_ptr<Command> cmd);
	void AddCommand(std::vector<EDK3::ref_ptr<Command>> *displayList,
					EDK3::ref_ptr<Command> cmd);

	void SetPredefiniedShape(EDK3::ref_ptr <Geometry> geo, Geometry::BasicShapes shape);
	void SetPredefiniedMaterial(EDK3::ref_ptr <Material> mat, Material::BasicMaterials basic_mat);


	EDK3::ref_ptr<Audio3D> newSong;

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

	void Input();
	void Update();
	void Draw();

	// Threads
	EDK3::ref_ptr<Thread> logic_;
	EDK3::ref_ptr<Thread> render_;
	EDK3::ref_ptr<Thread> input_;
	EDK3::ref_ptr<Thread> audio_;

	// Audio STUFF
	std::vector<EDK3::ref_ptr<Command>> audio_dl_;

	// DisplayLists Stuff
	void Audio();
	void PrepareAudio();


};

// --------------------------------------------------------------//


#endif // __SUFFER_MANAGER_H__
