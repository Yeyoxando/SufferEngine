/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 10-12-2019
* Material Header
*/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <glm.hpp>
#include <data_types.h>
#include <referenced.h>
#include <ref_ptr.h>

namespace Suffer {

	// --------------------------------------------------- //

	class Material : public Referenced {

	public:
		friend class DrawGeometry;


		Material();

    class MaterialSettings : public Referenced {
    public:
      MaterialSettings();
      ~MaterialSettings();


      enum ParamsType {
        kParams_Default = 0,
        kParams_Phong,
        kParams_NONE = 20
      };

      struct DefaultParams {
        friend class MaterialSettings;
      public:
        DefaultParams();
        ~DefaultParams() {}

      private:
        glm::vec4 color_;
      };

      struct PhongParams {
        friend class MaterialSettings;
        PhongParams();
        ~PhongParams() {}

      private:
        glm::vec4 color_;

      };

      union Params {
        Params();
        ~Params();

        DefaultParams default_params_;
        PhongParams phong_params_;
      };


      // Getters
      glm::vec4 GetColor() const;

      // Setters
      void SetColor(glm::vec4 new_color);

      Params material_params_;

      ParamsType params_type_;
    };

    void SetMaterialParamsType(MaterialSettings::ParamsType type);
    u32 GetMaterialParamsType() const;

    ref_ptr<MaterialSettings> material_settings_;


	protected:
		virtual ~Material();

	private:

		struct Data;
		Data* data_;

		// Methods
		Material(const Material&);
	};
}

// --------------------------------------------------- //

#endif // __MATERIAL_H__