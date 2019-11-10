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

		enum MaterialType {
			kBasicMaterials_Default = 0,
			kBasicMaterials_Phong,
			kBasicMaterials_NONE = 20
		};


		Material();

    void SetMaterialType(MaterialType type);
    u32 GetMaterialType();

    class MaterialSettings : public Referenced {
    public:
      MaterialSettings();
      ~MaterialSettings();

      struct DefaultParams {
      public:
        DefaultParams();
        ~DefaultParams() {}

        // Getters
        glm::vec4 GetColor();

        // Setters
        void SetColor(glm::vec4 new_color);

      private:
        glm::vec4 color_;
      };

      struct PhongParams {
        PhongParams();
        ~PhongParams() {}

        // Getters
        glm::vec4 GetColor();

        // Setters
        void SetColor(glm::vec4 new_color);

      private:
        glm::vec4 color_;

      };

      union Params {
        Params();
        ~Params();

        DefaultParams default_params_;
        PhongParams phong_params_;
      };

      Params material_params_;
    };

    ref_ptr<MaterialSettings> material_settings_;


	protected:
		virtual ~Material();

	private:

		struct Data;
		Data* data_;

		MaterialType material_type_;

		// Methods
		Material(const Material&);
	};
}

// --------------------------------------------------- //

#endif // __MATERIAL_H__