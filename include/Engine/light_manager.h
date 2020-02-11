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

  public:

    // ----------------------------------------------------------------------- //

    class Light : public Referenced {

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


      float* Color();
      bool   Active();
      float* Position();
      float* Direction();
      float  Intensity();

    protected:
      Light();
      ~Light();

      mathmorra::Vector3 color_;
      mathmorra::Vector3 position_;
      mathmorra::Vector3 direction_;
      float intensity_;
      bool active_;

    };

    // ----------------------------------------------------------------------- //

    class DirectionalLight : public Light {
    public:
      DirectionalLight();
      ~DirectionalLight();

    };

    // ----------------------------------------------------------------------- //

    class PointLight : public Light {
    public:
      PointLight();
      ~PointLight();

    };

    // ----------------------------------------------------------------------- //

    class SpotLight : public Light {
    public:
      SpotLight();
      ~SpotLight();

    };

    // ----------------------------------------------------------------------- //

  private:
    LightManager();
    ~LightManager();

    void StartUp();  // a.k.a Init()
    void ShutDown(); // a.k.a End()
    

    u32 current_lights_;
    std::vector<Light*> lights_;

  };

}
#endif