// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __SUFFER_MANAGER_H__
#define __SUFFER_MANAGER_H__

#include <vector>
#include <game_object.h>
#include <geometry.h>
#include <material.h>
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

	void SetPredefiniedShape(EDK3::ref_ptr <Geometry> geo, Geometry::BasicShapes shape);
	void SetPredefiniedMaterial(EDK3::ref_ptr <Material> mat, Material::BasicMaterials basic_mat);

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
