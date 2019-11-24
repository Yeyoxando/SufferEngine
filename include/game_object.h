/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* GameObject Header (Transform)
*/

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <geometry.h>
#include <material.h>
#include <data_types.h>
#include <referenced.h>
#include <ref_ptr.h>
#include <command.h>
#include "display_list.h"

// LUA
#include "lua.hpp"
#include <cstdlib>
#include <cassert>

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
      friend class Scene;
	public:

		GameObject();
		GameObject(const GameObject& go);

    // Operators
    bool operator!=(const GameObject& go);
    bool operator==(const GameObject& go);

		// Getters
		Transform GetTransform();
		ref_ptr<MaterialInstance> GetMaterial();
		ref_ptr<Geometry> GetGeometry();

		// Setters
		void SetMaterial(ref_ptr<MaterialInstance> new_material);
		void SetGeometry(ref_ptr<Geometry> new_geometry);

    void AddDrawCommand(Suffer::DisplayList& dl, mathmorra::Matrix4 view, mathmorra::Matrix4 projection);


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
    void Scale(mathmorra::Vector3 scale);
    void Scale(float x, float y, float z);

    const char* Name();
    void SetName(const char* name);

    // LUA Stuff
    lua_State* _script = nullptr;
    static GameObject* GetReference(lua_State* L);
    void StartUp(const char* luaCodeFile);
    void CheckLuaError(int status);

    void RotateL(int x, int y, int z) {
        static float x_ = x;
        static float y_ = y;
        static float z_ = z;
        x_ += (0.02f) * x;
        y_ += (0.02f) * y;
        z_ += (0.02f) * z;
        Rotate(x_, y_, z_);
    }

    static int lua_Rotate(lua_State* L) {
        // This receives a stack with values...
        int args = lua_gettop(L);
        if (args != 3) {
            return luaL_error(L, "Invalid call expected three argument");
        }
        float x = lua_tonumber(L, 1);
        float y = lua_tonumber(L, 2);
        float z = lua_tonumber(L, 3);
        GetReference(L)->RotateL(x, y, z);
        lua_pop(L, 1);
        return 0;
    }

	protected:
		virtual ~GameObject();

	private:

		// Attributes
		Transform transform_;
		ref_ptr<MaterialInstance> material_;
		ref_ptr<Geometry> geometry_;

    char* name_;

		// Methods
    void Step(float delta_time);
    void Destroy();

	};

} // End of Suffer namespace

// --------------------------------------------------- //

#endif // __GAME_OBJECT_H__