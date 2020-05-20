/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 12-12-2019
* MaterialComponent Header
*/

#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "component.h"
#include "resource_manager.h"
#include <referenced.h>
#include <ref_ptr.h>
#include "vector2.h"
#include "vector4.h"
#include <vector>

namespace Suffer {

  class MaterialComponent : public Component {
    friend class DrawGeometry;
  public:
    MaterialComponent();

    /**
    * @brief: Indicates which type of material is it
    */
    enum ParamsType {
      kParamsType_Invalid = -1,
      kParamsType_BlinnPhong = 0,
      kParamsType_RenderToTexture = 1,
      kParamsType_BlinnPhongNM = 2,
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
     * @brief: Saves basic blinn phong material specific parameters.
     */
    struct BlinnPhongParams : public BaseParams {
      friend class DrawGeometry;
      friend class Interface;
    public:
      BlinnPhongParams();
      ~BlinnPhongParams() {}

      float specular_strength_;
      float specular_pow_;
      float reflection_strength_;

      mathmorra::Vector2 tiling_;

      void SetAlbedoTexture(ResourceManager::Texture* texture);
      void SetSpecularTexture(ResourceManager::Texture* texture);
      void SetNormalMap(ResourceManager::Texture* texture);
      void SetReflectionTexture(ResourceManager::Texture* texture, float reflection_strength);

    private:
      s32 albedo_texture_id_;
      s32 specular_texture_id_;
      s32 normal_map_texture_id_;
      s32 reflection_texture_id_;

      float u_time_;

      bool use_albedo_texture_;
      bool use_specular_texture_;
      bool use_normal_map_texture_;
      bool use_reflection_texture_;

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
    void AddParams(ref_ptr<BaseParams> params);

    /**
     * @return: current material component params
     */
    BaseParams* CurrentParams(u32 params_id = 0);

  protected:
    virtual ~MaterialComponent();

  private:
    std::vector<ref_ptr<BaseParams>> current_params_;
    u32 current_params_number_;

  };

}

#endif //  __COMPONENT_MATERIAL_H__