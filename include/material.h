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
#include "vector4.h"

namespace Suffer {

	// --------------------------------------------------- //

	class MaterialInstance : public Referenced {

	public:
		friend class DrawGeometry;

		MaterialInstance();

    enum ParamsType {
      kParams_Default = 0,
      kParams_Phong,
      kParams_NONE = 20
    };

    // Getters
    float* GetColor() const;

    // Setters
    void SetColor(mathmorra::Vector4 new_color);


    void SetMaterialParamsType(ParamsType type);
    u32 GetMaterialParamsType() const;


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