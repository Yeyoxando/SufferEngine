#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <game_object.h>
#include <referenced.h>
#include <ref_ptr.h>

using namespace Suffer;

class Scene : public Referenced{

public:

	Scene();
	Scene(const Scene&);
	virtual ~Scene();

	void Init();
	void PrepareDraw();

	// Methods

	// Attributes
	std::vector<EDK3::ref_ptr<GameObject>> go_;

};

#endif // __SCENE_H__
