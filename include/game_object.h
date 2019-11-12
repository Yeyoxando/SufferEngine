/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* GameObject Header (Material, Transform, Geometry)
*/

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <geometry.h>
#include <material.h>
#include <data_types.h>
#include <referenced.h>
#include <ref_ptr.h>
#include <command.h>

// Mathematic Headers
#include <vector3.h>
#include <matrix4.h>


namespace Suffer {

	// --------------------------------------------------- //

	struct Transform {

	public:
		mathmorra::Vector3 scale_;
		mathmorra::Vector3 position_;
		mathmorra::Vector3 rotation_;

    mathmorra::Vector3 up_;
    mathmorra::Vector3 right_;
    mathmorra::Vector3 forward_;

	};

	// --------------------------------------------------- //

	class GameObject : public virtual Referenced {

	public:

		GameObject();
		GameObject(const GameObject& go);

    // Operators
    bool operator!=(const GameObject& go);
    bool operator==(const GameObject& go);

		// Getters
		Transform GetTransform();
		const ref_ptr<Material> GetMaterial();
		const ref_ptr<Geometry> GetGeometry();

		// Setters
		void SetMaterial(ref_ptr<Material> new_material);
		void SetGeometry(ref_ptr<Geometry> new_geometry);

		ref_ptr<Command> GetDrawCommand();


    // Hierarchy Stuff
    void DetachChildren();
    void RemoveChild(u32 child);
    GameObject* GetChild(u32 child);
    
    u32 NumberChilds();
    u32 NumberChildsRecursively(GameObject* go);

    // Transform
    void Rotate(float x, float y, float z);
    void Translate(float x, float y, float z);
    void Translate(mathmorra::Vector3 position);

    const char* Name();
    void SetName(const char* name);

	protected:
		virtual ~GameObject();

	private:
		// Attributes
		Transform transform_;
		ref_ptr<Material> material_;
		ref_ptr<Geometry> geometry_;

    char* name_;

		// Methods
    void Step(float delta_time);
    void Destroy();

	};

} // End of Suffer namespace

// --------------------------------------------------- //

#endif // __GAME_OBJECT_H__