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
        explicit Component() : kind_(kComponentKind_Invalid) {}

      enum ComponentKind {
          // INIT WITH THE LAST ELEMENT OF THE USER ENUMS
          kComponentKind_Invalid = -1,
          kComponentKind_Transform,
          kComponentKind_Material ,
          kComponentKind_Visibility,
          kComponentKind_Script,
          kComponentKind_Renderer,
      };

      ComponentKind kind_;

  protected:
      virtual ~Component();

  };

}
#endif // __COMPONENT_H__
