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
#include <command.h>

// SCHEDULER

// --------------------------------------------------------------//

class SufferManager {

public:
	static SufferManager& instance();

	friend class Audio3D;
	friend class Audio2D;

	bool Init();
	bool Run();
	bool Step(double time_step);
	bool Finish();

	double DeltaTime();
	void AddCommand(EDK3::ref_ptr<Command> cmd);

	void SetPredefiniedShape(EDK3::ref_ptr <Geometry> geo, Geometry::BasicShapes shape);
	void SetPredefiniedMaterial(EDK3::ref_ptr <Material> mat, Material::BasicMaterials basic_mat);


	void Draw();
	void Logic();
	void Input();
	void Update();
	void Audio();

	EDK3::ref_ptr<Audio3D> newSong;

	std::mutex render_mutex;

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

	// DisplayLists Stuff
	void PrepareAudio();


};

// --------------------------------------------------------------//


#endif // __SUFFER_MANAGER_H__
