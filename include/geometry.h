/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* Geometry Header
*/

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <referenced.h>
#include <ref_ptr.h>
#include <resource_manager.h>
#include <data_types.h>

// --------------------------------------------------- //

namespace Suffer {

	class Geometry : public virtual Referenced {

	public:
		friend class DrawGeometry;

		Geometry();

		enum BasicShapes {
			kBasicShapes_Triangle = 0,
			kBasicShapes_Quad,
			kBasicShapes_Cube,
			kBasicShapes_NONE = 20
		};

		void SetVertexBuffer(ResourceManager::VertexBuffer vertex_buffer);
		void SetIndexBuffer(ResourceManager::IndexBuffer index_buffer);

		s32 VertexBuffer();
		s32 IndexBuffer();

	protected:
		virtual ~Geometry();

	private:

		struct Data;
		Data* data_;

		BasicShapes shape_;

		ResourceManager::VertexBuffer vertex_buffer_;
		ResourceManager::IndexBuffer index_buffer_;

		// Methods
		Geometry(const Geometry&);
	};
}

// --------------------------------------------------- //

#endif // __GEOMETRY_H__