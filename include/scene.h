/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-14-2019
 * Scene Header : Referenced
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <game_object.h>
#include <referenced.h>

using namespace Suffer;

class Scene : public Referenced {

public:

	Scene();
	Scene(const Scene&);
	virtual ~Scene();
	
	// Methods

	// Attributes
	std::vector<GameObject> go_;

};

#endif // __SCENE_H__