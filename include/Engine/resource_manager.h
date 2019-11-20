// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "scoped_array.h"
#include "referenced.h"
#include "ref_ptr.h"
#include "vector3.h"
#include "vector2.h"

namespace Suffer {

  /**
    * @brief:
    */
  class ResourceManager {
    friend class DrawGeometry;
    friend class SufferManager;

  public:
    ResourceManager();
    ~ResourceManager();

    /**
    * @brief:
    */
    class GPUResource : public Referenced {

    public:
      GPUResource();
      ~GPUResource();

      /**
      * @brief:
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


    // ----------------------------- VertexBuffer -------------------------- //

    /**
    * @brief: 
    */
    class VertexBuffer : public GPUResource {
    public:
      friend class SufferManager;

      /**
      * @brief:
      */
      enum VertexFormat {
        kVertexFormat_3P = 0,
        kVertexFormat_3P_3N = 1,
        kVertexFormat_3P_3N_2UV = 2,
        kVertexFormat_Invalid
      };

      /**
      * @brief:
      */
      struct Vertex {
        Vertex() {}
        Vertex(mathmorra::Vector3 vertex) {}
        Vertex(mathmorra::Vector3 vertex, mathmorra::Vector3 normal) {}
        Vertex(mathmorra::Vector3 vertex, mathmorra::Vector3 normal, mathmorra::Vector2 uv) {}
        ~Vertex() {}

        mathmorra::Vector3 vertices_;
        mathmorra::Vector3 normals_;
        mathmorra::Vector2 uvs_;

      };

      VertexBuffer();
      ~VertexBuffer() {};

      VertexFormat format_;

    };

    /**
       * @brief:
       * @param:
       * @param:
       */
    void UploadVertexData(const ref_ptr<VertexBuffer> buffer, Array<float> *data);

    /**
       * @brief:
       * @param:
       * @param:
       * @param:
       */
    void UploadVertexData(const ref_ptr<VertexBuffer> buffer, float* data, u32 size);

    // ----------------------------- VertexBuffer -------------------------- //



    // ----------------------------- IndexBuffer --------------------------- //

    /**
    * @brief:
    */
    class IndexBuffer : public GPUResource {
    public:
      IndexBuffer();
      ~IndexBuffer() {};

      /**
      * @brief:
      */
      struct Triangle {
        Triangle() {}
        Triangle(u16 indices[3]) {}
        ~Triangle() {}

        u16 indices_[3];

      };

    };

    /**
       * @brief:
       * @param:
       * @param:
       */
    void UploadIndexData(const ref_ptr<IndexBuffer> buffer, Array<u16> *data);

    /**
       * @brief:
       * @param:
       * @param:
       * @param:
       */
    void UploadIndexData(const ref_ptr<IndexBuffer> buffer, u16* data, u32 size);

    // ----------------------------- IndexBuffer --------------------------- //



    // ------------------------------- Texture ----------------------------- //

    /**
    * @brief:
    */
    class Texture : public GPUResource {
    public:
      Texture();
      ~Texture() {};

      enum TextureWrap {
        kTextureWrap_Repeat = 0,
        kTextureWrap_MirroredRepeat,
        kTextureWrap_ClampToEdge,
      };

      enum TextureFilter {
        kTextureFilter_Linear = 0,
        kTextureFilter_Nearest,
      };

      void SetTextureWrap(TextureWrap wrap_s, TextureWrap wrap_t);
      void SetTextureFilter(TextureFilter min_filter, TextureFilter mag_filter);

    };
    

    /**
       * @brief:
       * @param:
       * @param:
       */
    void LoadTextureData(const ref_ptr<Texture> texture, const char* file);

    // ------------------------------- Texture ----------------------------- //


  private:
    void StartUp(); // a.k.a Init()
    void ShutDown(); // a.k.a End()


    struct ResourceData;
    ResourceData* data_;

  };

}


#endif //__RESOURCE_MANAGER_H__