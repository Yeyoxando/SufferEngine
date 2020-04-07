/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* GameObject Header (Transform)
*/

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <data_types.h>
#include <referenced.h>
#include <ref_ptr.h>
#include <command.h>
#include "display_list.h"
#include <list>

// Mathematic Headers
#include <vector3.h>
#include <matrix4.h>

// ECS
#include <map>
#include "component.h"
#include "component_transform.h"

namespace Suffer {

	// --------------------------------------------------- //

	class GameObject : public virtual Referenced {
      friend class Scene;
      friend class SufferManager;

	public:
      enum Archetype {
          kArchetype_Invalid,
          kArchetype_Drawable,
      };


		GameObject();
		GameObject(const GameObject& go);

    // Operators
    bool operator!=(const GameObject& go);
    bool operator==(const GameObject& go);

    // Components
    std::map <s32, ref_ptr<Component>> components_;

    Component* GetComponent(Component::ComponentKind component);
    bool HasComponent(Component::ComponentKind component);
    void AddComponent(ref_ptr<Component> new_component);
    void RemoveComponent(Component::ComponentKind component);

    // Hierarchy Stuff
    void AddChild(ref_ptr<GameObject> child);
    void DetachChildren();
    void RemoveChild(u32 child);
    GameObject* GetChild(u32 child);
    
    u32 NumberChilds();
    u32 NumberChildsRecursively(GameObject* go);
    u32 ID();

    void SetArchetype(Archetype new_archetype);

    const char* Name();
    void SetName(const char* name);

	protected:
		virtual ~GameObject();

	private:

		// Attributes
    const char* name_;

		// Methods
    void Step(float delta_time);
    void Destroy();

    u32 id_;
    std::list<ref_ptr<GameObject>> childs_;

	};

} // End of Suffer namespace

// --------------------------------------------------- //

#endif // __GAME_OBJECT_H__