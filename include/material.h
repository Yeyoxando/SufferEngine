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
    * @brief:
    */
	class MaterialInstance : public Referenced {

	public:
		friend class DrawGeometry;

		MaterialInstance();

    /**
    * @brief:
    */
    enum ParamsType {
      kParams_Default = 0,
      kParams_Phong,
      kParams_NONE = 20
    };

    // ------------------------------ Getters ------------------------------ //

    /**
       * @return:
       */
    float* GetColor() const;
    /**
       * @return: 
       */
    u32 GetAlbedoTexture() const;
    /**
       * @return:
       */
    u32 GetMaterialParamsType() const;


    // ------------------------------ Getters ------------------------------ //

    /**
       * @return:
       */
    void SetColor(mathmorra::Vector4 new_color);

    /**
       * @return:
       */
    void SetAlbedoTexture(ref_ptr<ResourceManager::Texture> texture);

    /**
       * @return:
       */
    void SetMaterialParamsType(ParamsType type);


	protected:
		virtual ~MaterialInstance();

	private:
    ParamsType params_type_;

		struct Data;
		Data* data_;

		// Methods
		MaterialInstance(const MaterialInstance&);
	};
}

// --------------------------------------------------- //

#endif // __MATERIAL_H__