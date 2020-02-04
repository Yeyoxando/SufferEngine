/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 12-12-2019
* ComponentMaterial Header
*/

#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "component.h"
#include <referenced.h>
#include <ref_ptr.h>
#include "vector4.h"

namespace Suffer {

  class Material : public Component {
    friend class DrawGeometry;
  public:
    Material() : Component(kComponentKind_Material) { current_params_ = nullptr; }

    /**
    * @brief: Indicates which type of material is it
    */
    enum ParamsType {
      kParamsType_Invalid = -1,
      kParamsType_Default = 0,
      kParamsType_Unlit = 1,
      kParamsType_RenderToTexture = 2,
    };


    /**
     * @brief: BaseParams class from which inherit the rest of material params.
     *         If an attribute is needed in all the rest of material params it will be here.
     */
    struct BaseParams : public Referenced {
    public:
      mathmorra::Vector4 color_;
      ParamsType params_type_;

    protected:
      BaseParams();
      ~BaseParams() {}

    };

    /**
     * @brief: Saves default material specific parameters.
     */
    struct DefaultParams : public BaseParams {
    public:
      DefaultParams();
      ~DefaultParams() {}

      s32 albedo_texture_id_;

    };

    /**
     * @brief: Saves unlit material specific parameters.
     */
    struct UnlitParams : public BaseParams {
    public:
      UnlitParams();
      ~UnlitParams() {}

      float u_time_;

    };

    /**
     * @brief: Saves unlit material specific parameters.
     */
    struct RenderToTextureParams : public BaseParams {
    public:
      RenderToTextureParams();
      ~RenderToTextureParams() {}

      s32 albedo_texture_id_;

    };

    //struct ...Params : public BaseParams {};

    // ------------------------------ Setters ------------------------------ //

    /**
     * @brief: sets material instance default material parameters. Converts the material to a default type.
     * @param: default params for the object.
     */
    void SetParams(ref_ptr<BaseParams> params);

  protected:
    virtual ~Material();

  private:

    ref_ptr<BaseParams> current_params_;

  };

}

#endif //  __COMPONENT_MATERIAL_H__