#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <game_object.h>
#include <referenced.h>
#include <ref_ptr.h>

namespace Suffer {

	class Scene : public Referenced {

	public:

		Scene();
		Scene(const Scene&);
		virtual ~Scene();

		void Init();
		void Step(float time_step);
		void PrepareDraw();

		// Methods
    void AddGameObject(ref_ptr<GameObject> gameobject);


  private:
		// Attributes
		std::vector<ref_ptr<GameObject>> current_gameobjects_;

	};

}

#endif // __SCENE_H__
