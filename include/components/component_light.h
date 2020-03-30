/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-27-2019
* ComponentLight Header
*/

#ifndef __COMPONENT_LIGHT_H__
#define __COMPONENT_LIGHT_H__

#include "component.h"
#include "light_manager.h"
#include "matrix4.h"

namespace Suffer {

    class LightComponent : public Component {
        friend class SystemLight;
        friend class GameObject;
        friend class ShadowMap;
        friend class ShadowCubemap;
        friend class DrawGeometry;

    public:
        enum LightKind {
            kLightKind_Invalid = -1,
            kLightKind_Directional = 0,
            kLightKind_Point = 1,
            kLightKind_Spot = 2
        };

        LightComponent() : Component(kComponentKind_Light) { initialized_ = false;  };
        LightKind kind_;

        void Init(LightKind kind);
        void Reset();


        void SetActive(bool active);
        void SetIntensity(float new_intensity);

        void SetColor(float* new_color);
        void SetColor(float r, float g, float b);
        void SetColor(mathmorra::Vector3 new_color);

        void SetPosition(float* new_position);
        void SetPosition(float x, float y, float z);
        void SetPosition(mathmorra::Vector3 new_position);

        void SetDirection(float* new_direction);
        void SetDirection(float x, float y, float z);
        void SetDirection(mathmorra::Vector3 new_direction);

        void SetAmbient(float* new_ambient);
        void SetAmbient(float x, float y, float z);
        void SetAmbient(mathmorra::Vector3 new_ambient);

        void SetDiffuse(float* new_diffuse);
        void SetDiffuse(float x, float y, float z);
        void SetDiffuse(mathmorra::Vector3 new_diffuse);

        void SetSpecular(float* new_specular);
        void SetSpecular(float x, float y, float z);
        void SetSpecular(mathmorra::Vector3 new_specular);

        void SetLinear(float new_linear = 1.0f);
        void SetConstant(float new_constant = 0.09f);
        void SetQuadratic(float new_quadratic = 0.032f);
        void SetCutOff(float new_cut_off = 0.9978f);
        void SetOuterCutOff(float new_outer_cut_off = 0.99f);


        float* Color();
        bool   Active();
        float* Position();
        float* Direction();
        float* Ambient();
        float* Diffuse();
        float* Specular();
        float  Intensity();
        float  CutOff();
        float  OuterCutOff();
        float  Quadratic();
        float  Linear();
        float  Constant();
        u16 GetLightKind();
        void SetLightKind(LightKind new_kind);

    private:
        bool initialized_;
        LightManager::DirectionalLight* reference_;

    };

}

#endif // __COMPONENT_LIGHT_H__
