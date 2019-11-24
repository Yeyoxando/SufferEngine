/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 10-12-2019
* MaterialInstance Header
*/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <data_types.h>
#include <referenced.h>
#include <ref_ptr.h>
#include "resource_manager.h"
#include "vector4.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: contain the material kind and the attributes to render with it
   */
	class MaterialInstance : public Referenced {

	public:
		friend class DrawGeometry;

		MaterialInstance();

    /**
     * @brief: Indicates which type of material is it
     */
    enum ParamsType {
      kParams_Default = 0,
      kParams_Phong,
      kParams_NONE = 20,
    };


    /**
     * @brief: BaseParams class from which inherit the rest of material params.
     *         If an attributte is needed in all the rest of material params it will be here.
     */
    struct BaseParams : public Referenced {    
      friend class MaterialInstance;
    public:
      mathmorra::Vector4 color_;

    protected:
      BaseParams();
      ~BaseParams() {}

      ParamsType params_type_;

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
     * @brief: Saves phong material specific parameters.
     */
    struct PhongParams : public BaseParams {
    public:
      PhongParams();
      ~PhongParams() {}

      s32 albedo_texture_id_;

    };

    //struct ...Params : public BaseParams {};

    // ------------------------------ Setters ------------------------------ //

    /**
     * @brief: sets material instance default material parameters. Converts the material to a default type.
     * @param: default params for the object.
     */
    void SetDefaultParams(ref_ptr<DefaultParams> params);

    /**
     * @brief: sets material instance phong material parameters. Converts the material to a phong type.
     * @param: phong params for the object.
     */
    void SetPhongParams(ref_ptr<PhongParams> params);


	protected:
		virtual ~MaterialInstance();

  private:
    u32 GetMaterialParamsType() const;
    BaseParams* GetMaterialParams();

		struct Data;
		Data* data_;

	};

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // __MATERIAL_H__