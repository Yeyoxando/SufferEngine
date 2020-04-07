/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 03-01-2020
* ComponentChild Header
*/

#ifndef __COMPONENT_CHILD_H__
#define __COMPONENT_CHILD_H__

#include "component.h"
#include "vector3.h"
#include "matrix4.h"
#include "game_object.h"

namespace Suffer {

    class ChildComponent : public Component {
        friend class SystemTransform;
        friend class GameObject;
        friend class SystemHierarchy;

    public:
        ChildComponent() : Component(kComponentKind_Child) { Init(); };

    protected:

        void Init();
        ~ChildComponent();

    private:
        GameObject* parent_reference_;

    };

} // End of Suffer namespace

#endif // __COMPONENT_CHILD_H__
