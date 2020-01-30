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
	public:

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
    void DetachChildren();
    void RemoveChild(u32 child);
    GameObject* GetChild(u32 child);
    
    u32 NumberChilds();
    u32 NumberChildsRecursively(GameObject* go);

    const char* Name();
    void SetName(const char* name);
    void StartUpLUA(const char* luaCodeFile);

	protected:
		virtual ~GameObject();

	private:

		// Attributes
    const char* name_;

		// Methods
    void Step(float delta_time);
    void Destroy();

    struct Data;
    Data* data_;

	};

} // End of Suffer namespace

// --------------------------------------------------- //

#endif // __GAME_OBJECT_H__