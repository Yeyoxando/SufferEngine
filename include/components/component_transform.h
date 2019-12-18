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

    class Transform : public Component {
        friend class SystemTransform;
    public:
      Transform() : Component(kComponentKind_Transform) { Init(); };

        void Scale(float x, float y, float z);
        void Rotate(float x, float y, float z);
        void Translate(float x, float y, float z);

        void Scale(mathmorra::Vector3 scale);
        void Rotate(mathmorra::Vector3 rotation);
        void Translate(mathmorra::Vector3 position);

        float* GetScale();
        float* GetRotation();
        float* GetPosition();

        mathmorra::Matrix4 GetModelMatrix();

    protected:

        void Init();

        mathmorra::Vector3 scale_;
        mathmorra::Vector3 position_;
        mathmorra::Vector3 rotation_;

        mathmorra::Vector3 up_;
        mathmorra::Vector3 right_;
        mathmorra::Vector3 forward_;

        mathmorra::Matrix4 model_;

        ~Transform();
    };

} // End of Suffer namespace

#endif // __COMPONENT_TRANSFORM_H__
