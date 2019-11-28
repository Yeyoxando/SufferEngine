/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-28-2019
* ComponentTransform Header
*/

#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRANSFORM_H__

#include "component.h"
#include "vector3.h"
#include "matrix4.h"

namespace Suffer {

    class TransformComponent : public Component {

    public:
        TransformComponent();

        mathmorra::Vector3 scale_;
        mathmorra::Vector3 position_;
        mathmorra::Vector3 rotation_;

        mathmorra::Matrix4 model_;

    protected:
        ~TransformComponent();
    };

} // End of Suffer namespace

#endif // __COMPONENT_TRANSFORM_H__
