// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __LIGHT_MANAGER_H__
#define __LIGHT_MANAGER_H__

#include "scoped_array.h"
#include "referenced.h"
#include "ref_ptr.h"
#include "vector3.h"

namespace Suffer {

  class LightManager {
    friend class SufferManager;

  public:

    // ----------------------------------------------------------------------- //

    class Light : public Referenced {
    protected:
      Light();
      ~Light();

      mathmorra::Vector3 position_;
      mathmorra::Vector3 direction_;
      mathmorra::Vector3 color_;
      float intensity_;

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

  };

}
#endif