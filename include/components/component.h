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

  public:

    enum ComponentKind {
      // INIT WITH THE LAST ELEMENT OF THE USER ENUMS
      kComponentKind_Invalid = -1,
      kComponentKind_Transform,
      kComponentKind_DebugGeometry,
      kComponentKind_Geometry,
      kComponentKind_Material,
      kComponentKind_Audio,
      kComponentKind_Script,
      kComponentKind_User = 1000,
    };

    explicit Component(ComponentKind kind) : kind_(kind) {}

    ComponentKind const kind_;

  protected:
    virtual ~Component();
  };

}
#endif // __COMPONENT_H__