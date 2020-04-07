// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "game_object.h"
#include "referenced.h"
#include "ref_ptr.h"
#include "camera.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: Contain all the GameObjects that represent a Scene.
   */
	class Scene : public Referenced {
      friend class Camera;
      friend class Interface;
      friend class SufferManager;
      friend class SystemLight;
      friend class System;

	public:
		Scene();
		Scene(const Scene&);
		virtual ~Scene();

    /**
     * @brief: Add a new GameObject to the scene.
     * @param: GameObject to add.
     */
    void AddGameObject(ref_ptr<GameObject> gameobject);
    void RemoveGameObject(GameObject* game_object);

    /**
     * @brief: Get the main camera of the current scene.
     * @return: a pointer to the main camera.
     */
    Camera* GetMainCamera();


  private:

    /**
     * @brief: Updates all the GameObjects of the scene and prepares a DisplayList.
     * @param: time_step to update the objects
     */
    void Step(float time_step);

		// Attributes
		std::vector<ref_ptr<GameObject>> current_gameobjects_;

    ref_ptr<Camera> main_camera_;

  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // __SCENE_H__
