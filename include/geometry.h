/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* Geometry Header
*/

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <data_types.h>
#include <referenced.h>
#include <ref_ptr.h>
#include <resource_manager.h>

namespace Suffer {

    class Geometry : public virtual Referenced {

    public:
	    friend class DrawGeometry;

	    Geometry();

      enum DrawMode {
          kDrawMode_Invalid   = -1,
          kDrawMode_Triangles = 0,
          kDrawMode_Lines,
          kDrawMode_LineLoop,
          kDrawMode_LineStrip,
          kDrawMode_Patches,
          kDrawMode_Points,
      };

      /**
      * @brief:
      */
	    enum BasicShapes {
        kBasicShapes_Invalid = -1,
		    kBasicShapes_Triangle = 0,
		    kBasicShapes_Quad,
		    kBasicShapes_Cube,
        kBasicShapes_Sphere,
		    kBasicShapes_NONE = 20
	    };

      void SetDrawMode(DrawMode newMode);
      DrawMode GetDrawMode();
		
      /**
       * @brief: Assigns the vertex buffer passed by parameter
       *         to the current GameObject Geometry.
       * @param: the vertex buffer.
       */
      void SetVertexBuffer(ref_ptr<Suffer::ResourceManager::VertexBuffer> buffer);

      /**
       * @brief: Assigns the index buffer passed by parameter
       *         to the current GameObject Geometry.
       * @param: the index buffer.
       */
      void SetIndexBuffer(ref_ptr<Suffer::ResourceManager::IndexBuffer> buffer);

      /**
       * @brief: Assigns the vertex and the index buffer passed by 
       *         parameter to the current GameObject Geometry.
       * @param: the vertex buffer.
       * @param: the index buffer.
       */
      void SetBuffers(ref_ptr<Suffer::ResourceManager::VertexBuffer> vertex_buffer, ref_ptr<Suffer::ResourceManager::IndexBuffer> index_buffer);

    protected:
	    virtual ~Geometry();

    private:

	    struct Data;
	    Data* data_;

      DrawMode mode_;
	    BasicShapes shape_;
      s32 index_buffer_id_;
      s32 vertex_buffer_id_;

      ref_ptr<Suffer::ResourceManager::IndexBuffer> index_buffer_;
      ref_ptr<Suffer::ResourceManager::VertexBuffer> vertex_buffer_;


	    // Methods
	    Geometry(const Geometry&);
    };

}
// --------------------------------------------------- //

#endif // __GEOMETRY_H__