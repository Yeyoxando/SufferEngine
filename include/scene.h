#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <game_object.h>

class Scene /*: public Referenced*/ {

public:

	Scene();
	Scene(const Scene&);
	virtual ~Scene();
	
	// Methods

	// Attributes
	std::vector<GameObject> go_;

};

#endif // __SCENE_H__