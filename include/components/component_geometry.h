/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 12-12-2019
* ComponentGeometry Header
*/

#ifndef __COMPONENT_GEOMETRY_H__
#define __COMPONENT_GEOMETRY_H__

#include "component.h"
#include <referenced.h>
#include <ref_ptr.h>
#include "vector4.h"
#include "resource_manager.h"

namespace Suffer {

  // TODO: Delete old Geometry and rename this to Geometry
  class GeometryComponent : public Component {

  public:
    friend class DrawGeometry;
    friend class DrawDepth;
    friend class DrawPointDepth;

    GeometryComponent();

    enum DrawMode {
      kDrawMode_Invalid = -1,
      kDrawMode_Triangles = 0,
      kDrawMode_Lines = 1,
      kDrawMode_LineLoop = 2,
      kDrawMode_LineStrip = 3,
      kDrawMode_Patches = 4,
      kDrawMode_Points = 5,
    };

    /**
    * @brief:
    */
    enum BasicShapes {
      kBasicShapes_Invalid = -1,
      kBasicShapes_Triangle = 0,
      kBasicShapes_Quad = 1,
      kBasicShapes_Cube = 2,
      kBasicShapes_Sphere = 3,
    };

    void CreateGeometryWithOBJ(const char* obj_file);

    void CreateGeometryWithShape(BasicShapes shape);
    BasicShapes GetGeometry();

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
    virtual ~GeometryComponent();

  private:

    DrawMode mode_;
    BasicShapes shape_;
    s32 index_buffer_id_;
    s32 vertex_buffer_id_;

    // Methods
    GeometryComponent(const GeometryComponent&) = delete;
  };

}

#endif //  __COMPONENT_GEOMETRY_H__