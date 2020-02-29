// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __LIGHT_MANAGER_H__
#define __LIGHT_MANAGER_H__

#include "scoped_array.h"
#include "referenced.h"
#include "ref_ptr.h"
#include "vector3.h"
#include <vector>

namespace Suffer {

  class LightManager {
    friend class SufferManager;
    friend class DrawGeometry;
    friend class Interface;

  public:

    enum LightKind {
      kLightKind_Invalid = -1,
      kLightKind_Directional = 0,
      kLightKind_Point = 1,
      kLightKind_Spot = 2,
    };

    // ----------------------------------------------------------------------- //

    class DirectionalLight : public Referenced {
    friend class LightComponent;

    public:
      
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


      float* Color();
      bool   Active();
      float* Position();
      float* Direction();
      float* Ambient();
      float* Diffuse();
      float* Specular();
      float  Intensity();
      u16 GetLightKind();
      void SetLightKind(LightKind new_kind);

      DirectionalLight();
      ~DirectionalLight();

    protected:
      mathmorra::Vector3 color_;
      mathmorra::Vector3 position_;
      mathmorra::Vector3 direction_;
      mathmorra::Vector3 ambient_;
      mathmorra::Vector3 diffuse_;
      mathmorra::Vector3 specular_;
      float intensity_;
      bool active_;
      u16 light_kind_;


    };

    // ----------------------------------------------------------------------- //

    class PointLight : public DirectionalLight {
    public:
      PointLight();
      ~PointLight();

      void SetConstant(float new_constant);
      void SetLinear(float new_linear);
      void SetQuadratic(float new_quadratic);

      float Constant();
      float Linear();
      float Quadratic();

    protected:
      float constant_;
      float linear_;
      float quadratic_;

    };

    // ----------------------------------------------------------------------- //

    class SpotLight : public PointLight {
    public:
      SpotLight();
      ~SpotLight();

      void SetCutOff(float new_cut_off);
      void SetOuterCutOff(float new_outer_cut_off);

      float CutOff();
      float OuterCutOff();

    private:
      float cut_off_;
      float outer_cut_off_;

    };

    // ----------------------------------------------------------------------- //

  private:
    LightManager();
    ~LightManager();

    void StartUp();  // a.k.a Init()
    void ShutDown(); // a.k.a End()
    

    u32 current_lights_;
    std::vector<ref_ptr<DirectionalLight>> lights_;

  };

}
#endif