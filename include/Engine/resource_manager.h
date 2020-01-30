// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "scoped_array.h"
#include "referenced.h"
#include "ref_ptr.h"
#include "vector3.h"
#include "vector2.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: Manages all the resources used in the Engine.
   */
  class ResourceManager {
    friend class DrawGeometry;
    friend class SufferManager;
    friend class GeometryComponent;

  public:

    // ------------------------------ GPUResource --------------------------- //

    /**
     * @brief: Basic class from which all gpu resources will inherit.
     */
    class GPUResource : public Referenced {

    public:
      GPUResource();
      ~GPUResource();

      /**
       * @brief: Indicates which kind of resource is
       */
      enum ResourceType {
        kVertexBuffer = 0,
        kIndexBuffer,
        kTexture,
        kFrameBuffer,
        kInvalid
      };

      s32 id_;

      ResourceType type_;

    };

    // ------------------------------ GPUResource --------------------------- //



    // ----------------------------- VertexBuffer -------------------------- //

    /**
     * @brief: Contain the vertexes information of a geometry to later use them
     *         to form triangles.
     */
    class VertexBuffer : public GPUResource {
    public:
      friend class SufferManager;

      /**
       * @brief: Indicates which attributes contain the vertexes to upload.
       */
      enum VertexFormat {
        kVertexFormat_3P = 0,
        kVertexFormat_3P_3N = 1,
        kVertexFormat_3P_3N_2UV = 2,
        kVertexFormat_Invalid
      };

      /**
       * @brief: struct to represent a vertex, compound by vertex position,
       *         vertex normals, and vertex uvs.
       */
      struct Vertex {
        Vertex() {}

        Vertex(float vertex_x, float vertex_y, float vertex_z);

        Vertex(float vertex_x, float vertex_y, float vertex_z,
          float normal_x, float normal_y, float normal_z);

        Vertex(float vertex_x, float vertex_y, float vertex_z, 
          float normal_x, float normal_y, float normal_z, 
          float uv_x, float uv_y);

        ~Vertex() {}

        mathmorra::Vector3 vertices_;
        mathmorra::Vector3 normals_;
        mathmorra::Vector2 uvs_;

      };

      VertexBuffer();
      ~VertexBuffer() {};

      /**
       * @brief: Indicates on which format are the uploaded vertex.
       * @param: format of the vertexes.
       */
      void SetVertexFormat(VertexFormat new_format);

      /**
       * @brief: Upload data to fill the buffer.
       * @param: array of vertex struct that form the geometry points.
       * @param: number of vertex to upload.
       */
      void UploadVertexData(VertexBuffer::Vertex* data, u32 size);

      /**
       * @brief: Upload data to fill the buffer.
       * @param: raw array of vertex data.
       * @param: number of floats, vertex * 3 floats, normals * 3 floats, uvs * 2 floats.
       */
      void UploadVertexData(float* data, u32 size);

    };

    // ----------------------------- VertexBuffer -------------------------- //



    // ----------------------------- IndexBuffer --------------------------- //

    /**
     * @brief: Contain the information to form the triangles of a geometry using indexes.
     */
    class IndexBuffer : public GPUResource {
    public:
      IndexBuffer();
      ~IndexBuffer() {};

      /**
       * @brief: Triangle structure formed by 3 indexes.
       */
      struct Triangle {
        Triangle() {}

        Triangle(u16 index1, u16 index2, u16 index3);

        ~Triangle() {}

        u16 indices_[3];

      };

      /**
       * @brief: Upload data to fill the buffer.
       * @param: Pointer to array of triangles that forms geometry indexes.
       * @param: number of triangles.
       */
      void UploadIndexData(IndexBuffer::Triangle* data, u32 size);

      /**
       * @brief: Upload data to fill the buffer.
       * @param: raw array of index data.
       * @param: number of indices.
       */
      void UploadIndexData(u16* data, u32 size);

    };

    // ----------------------------- IndexBuffer --------------------------- //



    // ------------------------------- Texture ----------------------------- //

    /**
     * @brief: Texture to draw with different materials.
     */
    class Texture : public GPUResource {
    public:
      Texture();
      ~Texture() {};

      /**
       * @brief: Possible s and t Wraps for a texture.
       */
      enum TextureWrap {
        kTextureWrap_Repeat = 0,
        kTextureWrap_MirroredRepeat,
        kTextureWrap_ClampToEdge,
      };

      /**
       * @brief: Possible min and mag filters for a texture.
       */
      enum TextureFilter {
        kTextureFilter_Linear = 0,
        kTextureFilter_Nearest,
      };

      /**
       * @brief: Sets the texture wrap options.
       * @param: wrap for horizontal axis (U of UVs).
       * @param: wrap for vertical axis (V of UVs).
       */
      void SetTextureWrap(TextureWrap wrap_s, TextureWrap wrap_t);
      /**
       * @brief: Sets the texture filters 
       * @param: min_filter to use when minification is needed.
       * @param: mag_filter to use when magnification is needed.
       */
      void SetTextureFilter(TextureFilter min_filter, TextureFilter mag_filter);
      
      /**
       * @brief: Loads an image from disk.
       * @param: file to read.
       */
      void LoadTextureData(const char* file);

    };

    // ------------------------------- Texture ----------------------------- //



  private:
    ResourceManager();
    ~ResourceManager();

    void StartUp(); // a.k.a Init().
    void ShutDown(); // a.k.a End().

    struct ResourceData;
    ResourceData* data_;

  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif //__RESOURCE_MANAGER_H__