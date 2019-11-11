/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* GameObject Header (Material, Transform, Geometry)
*/

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <geometry.h>
#include <material.h>
#include <data_types.h>
#include <referenced.h>
#include <ref_ptr.h>
#include <command.h>


namespace Suffer {

	// --------------------------------------------------- //

	struct Transform {

	public:
		glm::vec3 scale;
		glm::vec3 position;
		glm::vec3 rotation;

		glm::quat quat_rotation_;

	private:
		glm::mat4 model_;

	};

	// --------------------------------------------------- //

	class GameObject : public virtual Referenced {

	public:

		GameObject();
		GameObject(const GameObject& go);

		// Getters
		Transform GetTransform();
		const ref_ptr<Material> GetMaterial();
		const ref_ptr<Geometry> GetGeometry();

		// Setters
		void SetMaterial(ref_ptr<Material> new_material);
		void SetGeometry(ref_ptr<Geometry> new_geometry);

		ref_ptr<Command> GetDrawCommand();

    void SetPosition(glm::vec3 position);

	protected:
		virtual ~GameObject();

	private:
		// Attributes
		Transform transform_;
		ref_ptr<Material> material_;
		ref_ptr<Geometry> geometry_;

		// Methods

	};

} // End of Suffer namespace

// --------------------------------------------------- //

#endif // __GAME_OBJECT_H__