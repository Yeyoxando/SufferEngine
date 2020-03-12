/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 26-11-2019
* Component Header
*/

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "referenced.h"
#include "data_types.h"

namespace Suffer {

  class Component : public virtual Referenced {
    friend class GameObject;

  public:

    enum ComponentKind {
      // INIT WITH THE LAST ELEMENT OF THE USER ENUMS
      kComponentKind_Invalid        = -1,
      kComponentKind_Transform      =  0,
      kComponentKind_DebugGeometry  =  1,
      kComponentKind_Geometry       =  2,
      kComponentKind_Material       =  3,
      kComponentKind_Audio          =  4,
      kComponentKind_Script         =  5,
      kComponentKind_Light          =  6,
      kComponentKind_Child          =  7,
      kComponentKind_User = 1000,
    };

    explicit Component(ComponentKind kind) : kind_(kind) {}

    ComponentKind const kind_;

  protected:
    Suffer::GameObject* game_object_reference_;
    virtual ~Component();
  };

}
#endif // __COMPONENT_H__