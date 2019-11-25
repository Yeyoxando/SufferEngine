/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* GameObject Source (Transform)
*/

#include <game_object.h>
#include <draw_geometry.h>
#include <matrix4.h>
#include <imgui.h>
#include "interface.h"
#include <suffermanager.h>
#include "internal_interface.h"
#include "internal_game_object.h"

// --------------------------------------------------- //

Suffer::GameObject::GameObject() {

  transform_.scale_ = { 1.0f, 1.0f, 1.0f };
  transform_.position_ = { 0.0f, 0.0f, 0.0f };
  transform_.rotation_ = { 0.0f, 0.0f, 0.0f };

  transform_.up_ =    { 0.0f, 1.0f, 0.0f };
  transform_.right_ = { 1.0f, 0.0f, 0.0f };
  transform_.forward_ = mathmorra::Vector3::CrossProduct(transform_.up_, 
                                                         transform_.right_);

  data_ = new Data();

  name_ = "GameObject";
  data_->lua_error_ = false;

}

// --------------------------------------------------- //

Suffer::GameObject::~GameObject() {
    if (data_ == nullptr) return;
    delete data_;
    data_ = nullptr;
}

// --------------------------------------------------- //

bool Suffer::GameObject::operator!=(const GameObject& go){

    if (transform_.position_ !=  go.transform_.position_ ||
        transform_.scale_    !=  go.transform_.scale_    ||
        transform_.rotation_ !=  go.transform_.rotation_) 
    {
        return false;
    }

    // TODO: expand

}

// --------------------------------------------------- //

Suffer::GameObject::GameObject(const GameObject& go) {

	this->geometry_ = go.geometry_;
	this->material_ = go.material_;

}

// --------------------------------------------------- //

Suffer::ref_ptr<Suffer::MaterialInstance> Suffer::GameObject::GetMaterial() {
	return material_;
}

// --------------------------------------------------- //

Suffer::ref_ptr<Suffer::Geometry> Suffer::GameObject::GetGeometry() {
	return geometry_;
}

// --------------------------------------------------- //

void Suffer::GameObject::SetMaterial(ref_ptr<MaterialInstance> new_material) {

#ifdef ASSERT
	assert(new_material); // "newMaterial was NULL"
#endif
	material_ = new_material;
}

// --------------------------------------------------- //

void Suffer::GameObject::SetGeometry(ref_ptr<Geometry> new_geometry) {
#ifdef ASSERT
	assert(new_geometry); // "newGeometry was NULL"
#endif
	geometry_ = new_geometry;
}

// --------------------------------------------------- //

void Suffer::GameObject::AddDrawCommand(Suffer::DisplayList& dl, mathmorra::Matrix4 view, mathmorra::Matrix4 projection) {
  ref_ptr<DrawGeometry> draw_geometry;

  draw_geometry.alloc();
  draw_geometry.get()->SetData(this);

  mathmorra::Matrix4 model_matrix;

  mathmorra::Matrix4 translation_mat;
  translation_mat = translation_mat.Translate(transform_.position_.x_,
                                              transform_.position_.y_,
                                              transform_.position_.z_).Transpose();

  mathmorra::Matrix4 rotation_mat_x;
  mathmorra::Matrix4 rotation_mat_y;
  mathmorra::Matrix4 rotation_mat_z;
  rotation_mat_x = rotation_mat_x.RotateX(transform_.rotation_.x_);
  rotation_mat_y = rotation_mat_y.RotateY(transform_.rotation_.y_);
  rotation_mat_z = rotation_mat_z.RotateZ(transform_.rotation_.z_);

  rotation_mat_z = rotation_mat_z.Multiply(rotation_mat_y);
  rotation_mat_z = rotation_mat_z.Multiply(rotation_mat_x);

  mathmorra::Matrix4 scale_mat;
  scale_mat = scale_mat.Scale(transform_.scale_.x_,
    transform_.scale_.y_,
    transform_.scale_.z_);

  model_matrix = scale_mat * rotation_mat_z * translation_mat;

  draw_geometry.get()->SetModelMatrix(model_matrix);
  draw_geometry.get()->SetViewMatrix(view);
  draw_geometry.get()->SetProjectionMatrix(projection);

  dl.AddCommand(draw_geometry.get());

}

// --------------------------------------------------- //

void Suffer::GameObject::Translate(mathmorra::Vector3 position){
  transform_.position_ = position;
}

void Suffer::GameObject::Scale(mathmorra::Vector3 scale){
    transform_.scale_ = scale;
}

// --------------------------------------------------- //

void Suffer::GameObject::Scale(float x, float y, float z){
    transform_.scale_ = { x, y, z };
}

// --------------------------------------------------- //

const char* Suffer::GameObject::Name(){
    return name_;
}

// --------------------------------------------------- //

void Suffer::GameObject::SetName(const char* name){
    name_ = (char*)name;
}

Suffer::GameObject* Suffer::GameObject::Data::GetReference(lua_State* L) {
    
    lua_pushstring(L, "THIS");
    lua_gettable(L, LUA_REGISTRYINDEX);
    const void* raw_ptr = lua_topointer(L, -1);
    
    GameObject* ptr = reinterpret_cast<GameObject*>(const_cast<void*>(raw_ptr));
    if (ptr->data_ == nullptr) return nullptr;
    return ptr;
}

// --------------------------------------------------- //

void Suffer::GameObject::StartUpLUA(const char* luaCodeFile){

    data_->lua_file_ = (char*)luaCodeFile;
    assert(data_->_script == nullptr && "Invalid script");
    data_->_script = luaL_newstate();

    luaL_openlibs(data_->_script);

    // PUSH FUNCTIONS FOR LUA
    lua_pushcfunction(data_->_script, data_->lua_Rotate);    // +1
    lua_setglobal(data_->_script, "Rotate");                 // -1

    lua_pushcfunction(data_->_script, data_->lua_Translate); // +1
    lua_setglobal(data_->_script, "Translate");              // -1

    lua_pushcfunction(data_->_script, data_->lua_Scale);     // +1
    lua_setglobal(data_->_script, "Scale");                  // -1

    lua_pushcfunction(data_->_script, data_->lua_SetPredefinedGeometry);     // +1
    lua_setglobal(data_->_script, "SetPredefinedGeometry");                  // -1

    lua_pushcfunction(data_->_script, data_->lua_SetDrawMode);     // +1
    lua_setglobal(data_->_script, "SetDrawMode");                  // -1



    lua_pushstring(data_->_script, "THIS");
    lua_pushlightuserdata(data_->_script, this);
    lua_settable(data_->_script, LUA_REGISTRYINDEX);

    data_->reference = data_->GetReference(data_->_script);

}

// --------------------------------------------------- //


// --------------------------------------------------- //

Suffer::GameObject* Suffer::GameObject::GetChild(u32 child){
    // TODO: Expand this
    return &GameObject();
}

// --------------------------------------------------- //

u32 Suffer::GameObject::NumberChilds(){
    return 0;
}

// --------------------------------------------------- //

u32 Suffer::GameObject::NumberChildsRecursively(GameObject* go){

    u32 number_of_childs = go->NumberChilds();
    u32 result = 0;

    for (u32 i = 0; i < number_of_childs; ++i) {
        result = go->NumberChildsRecursively(go->GetChild(i));
    }

    return result;

}

// --------------------------------------------------- //

void Suffer::GameObject::Rotate(float x, float y, float z){
    transform_.rotation_ = { x, y, z };
}

// --------------------------------------------------- //

void Suffer::GameObject::Translate(float x, float y, float z){
    transform_.position_ = { x, y, z };
}

// --------------------------------------------------- //

Suffer::Transform Suffer::GameObject::GetTransform() {
	return transform_;
}

// --------------------------------------------------- //

void Suffer::GameObject::Step(float delta_time){

    // Updates
    if (!data_->lua_error_) {
      int status = luaL_dofile(data_->_script, data_->lua_file_);
      data_->CheckLuaError(status);
    }

    // Logic

}

// --------------------------------------------------- //

void Suffer::GameObject::Destroy(){
    // Destroy Himself
}

// --------------------------------------------------------------- //
/*
           _     _   _  ___         _____ _          __  __
          | |   | | | |/ _ \       /  ___| |        / _|/ _|
          | |   | | | / /_\ \      \ `--.| |_ _   _| |_| |_
          | |   | | | |  _  |       `--. \ __| | | |  _|  _|
          | |___| |_| | | | |      /\__/ / |_| |_| | | | |
          \_____/\___/\_| |_/      \____/ \__|\__,_|_| |_|
*/
// --------------------------------------------------------------- //

int Suffer::GameObject::Data::lua_Rotate(lua_State* L) {

    int arguments = lua_gettop(L);
    if (arguments != 3) {
        return luaL_error(L, "Invalid call expected three argument.");
    }
    float x = lua_tonumber(L, 1);
    float y = lua_tonumber(L, 2);
    float z = lua_tonumber(L, 3);

    GetReference(L)->data_->RotateL(x, y, z);

    lua_pop(L, 1);
    return 0;

}

// --------------------------------------------------------------- //

int Suffer::GameObject::Data::lua_Translate(lua_State* L){

    int arguments = lua_gettop(L);
    if (arguments != 3) {
        return luaL_error(L, "Invalid call, expected three arguments.");
    }
    float x = lua_tonumber(L, 1);
    float y = lua_tonumber(L, 2);
    float z = lua_tonumber(L, 3);

    GetReference(L)->data_->TranslateL(x, y, z);

    lua_pop(L, 1);
    return 0;

}

// --------------------------------------------------------------- //

int Suffer::GameObject::Data::lua_Scale(lua_State* L){

    int arguments = lua_gettop(L);
    if (arguments != 3) {
        return luaL_error(L, "Invalid call, expected three arguments");
    }

    float x = lua_tonumber(L, 1);
    float y = lua_tonumber(L, 2);
    float z = lua_tonumber(L, 3);
    GetReference(L)->Scale(mathmorra::Vector3(x, y, z));
    lua_pop(L, 1);
    return 0;

}

// --------------------------------------------------------------- //

int Suffer::GameObject::Data::lua_SetPredefinedGeometry(lua_State* L){

    int arguments = lua_gettop(L);
    if (arguments != 1) {
        return luaL_error(L, "Invalid call, expected one argument");
    }

    const char* x = lua_tostring(L, 1);

    Geometry::BasicShapes new_shape = Geometry::BasicShapes::kBasicShapes_Triangle;
    
    if (!strcmp(x, "Triangle")) new_shape = Geometry::BasicShapes::kBasicShapes_Triangle;
    if (!strcmp(x, "Quad"))     new_shape = Geometry::BasicShapes::kBasicShapes_Quad;
    if (!strcmp(x, "Cube"))     new_shape = Geometry::BasicShapes::kBasicShapes_Cube;
    if (!strcmp(x, "Sphere"))   new_shape = Geometry::BasicShapes::kBasicShapes_Sphere;

    GetReference(L)->GetGeometry()->CreateGeometryWithShape(new_shape);

    lua_pop(L, 1);
    return 0;

}

// --------------------------------------------------------------- //

int Suffer::GameObject::Data::lua_SetDrawMode(lua_State* L){

    int arguments = lua_gettop(L);
    if (arguments != 1) {
        return luaL_error(L, "Invalid call, expected one argument");
    }

    const char* x = lua_tostring(L, 1);

    Geometry::DrawMode draw_mode = Geometry::DrawMode::kDrawMode_Lines;

    if (!strcmp(x, "Lines"))     draw_mode = Geometry::DrawMode::kDrawMode_Lines;
    if (!strcmp(x, "LineLoop"))  draw_mode = Geometry::DrawMode::kDrawMode_LineLoop;
    if (!strcmp(x, "Points"))    draw_mode = Geometry::DrawMode::kDrawMode_Points;
    if (!strcmp(x, "Triangles")) draw_mode = Geometry::DrawMode::kDrawMode_Triangles;

    GetReference(L)->GetGeometry()->SetDrawMode(draw_mode);

    lua_pop(L, 1);
    return 0;

}

// --------------------------------------------------------------- //

void Suffer::GameObject::Data::CheckLuaError(int status) {

    if (status) {
        const char* error = lua_tostring(_script, -1);
        Interface::log.AddLog("\n[" _error_ "] [%s]", error);
        lua_error_ = true;
    }

}

// --------------------------------------------------------------- //

void Suffer::GameObject::Data::RotateL(float x, float y, float z) {

  reference->Rotate(reference->transform_.rotation_.x_ + x, 
                    reference->transform_.rotation_.y_ + y,
                    reference->transform_.rotation_.z_ + z);

}

// --------------------------------------------------------------- //

void Suffer::GameObject::Data::TranslateL(float x, float y, float z){

    reference->Translate(reference->transform_.position_.x_ + x,
                         reference->transform_.position_.y_ + y,
                         reference->transform_.position_.z_ + z);

}

// --------------------------------------------------------------- //