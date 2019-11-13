// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "scoped_array.h"
#include "referenced.h"
#include "ref_ptr.h"
#include "vector3.h"
#include "vector2.h"

namespace Suffer {

  class ResourceManager {
    friend class DrawGeometry;
    friend class SufferManager;

  public:
    ResourceManager();
    ~ResourceManager();

    class GPUResource : public Referenced {

    public:
      GPUResource();
      ~GPUResource();

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

    class VertexBuffer : public GPUResource {
    public:
      friend class SufferManager;
      enum VertexFormat {
        kVertexFormat_3P = 0,
        kVertexFormat_3P_3N = 1,
        kVertexFormat_Invalid
      };

      struct Vertex {
        Vertex() {}
        ~Vertex() {}

        mathmorra::Vector3 vertices_;
        mathmorra::Vector3 normals_;
        mathmorra::Vector2 uvs_;

      };

      VertexBuffer();
      ~VertexBuffer() {};

      VertexFormat format_;

    };

    class IndexBuffer : public GPUResource {
    public:
      IndexBuffer();
      ~IndexBuffer() {};

    };

    class Texture : public GPUResource {
    public:
      Texture();
      ~Texture() {};

    };

    //Buffers
    void UploadVertexData(const ref_ptr<VertexBuffer> buffer, Array<float> *data);
    void UploadVertexData(const ref_ptr<VertexBuffer> buffer, float* data, u32 size);
    void UploadIndexData(const ref_ptr<IndexBuffer> buffer, Array<u16> *data);
    void UploadIndexData(const ref_ptr<IndexBuffer> buffer, u16* data, u32 size);

  private:
    void StartUp();
    void ShutDown();


    struct ResourceData;
    ResourceData* data_;

  };

}


#endif //__RESOURCE_MANAGER_H__