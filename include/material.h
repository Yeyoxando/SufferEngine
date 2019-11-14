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

	// --------------------------------------------------- //

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
      kParams_NONE = 20
    };

    // ------------------------------ Getters ------------------------------ //

    /**
       * @return: color of the object
       */
    float* GetColor() const;
    /**
       * @return: albedo texture id 
       */
    u32 GetAlbedoTexture() const;
    /**
       * @return: Material params kind
       */
    u32 GetMaterialParamsType() const;


    // ------------------------------ Getters ------------------------------ //

    /**
       * @brief: sets object color
       * @param: new_color of the object  
       */
    void SetColor(mathmorra::Vector4 new_color);

    /**
       * @brief: sets object albedo texture
       * @param: previously created and loaded texture
       */
    void SetAlbedoTexture(ref_ptr<ResourceManager::Texture> texture);

    /**
       * @brief: sets the way that material should render and indicates which parameters could get
       * @param: type to set
       */
    void SetMaterialParamsType(ParamsType type);


	protected:
		virtual ~MaterialInstance();

	private:
    ParamsType params_type_;

		struct Data;
		Data* data_;


		MaterialInstance(const MaterialInstance&);
	};
}

// --------------------------------------------------- //

#endif // __MATERIAL_H__