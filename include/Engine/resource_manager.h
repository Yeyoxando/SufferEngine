#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <common_definitions.h>
#include <geometry.h>
#include <material.h>
#include <data_types.h>
#include <ref_ptr.h>

namespace Suffer {

    class ResourceManager {

        friend class SufferManager;

    public:

        struct IndexBuffer {

            IndexBuffer() { id_ = -1; };
            ~IndexBuffer() {};

            s32 id_;

            void Init(u32 size);
            u16 GetIndex(u32 index);

        };

        struct VertexBuffer {
            
            VertexBuffer() { id_ = -1; };
            ~VertexBuffer() {};

            enum VertexFormat {
                kVertexFormat_3P = 0,
                kVertexFormat_Invalid = 10
            };

            // Don't creates the buffer
            void Init(VertexFormat format, u32 size);
            float GetVertex(u32 index);


            s32 id_;

        };
        
        void UploadIndexData(const void* data, u32 size, u32 offset);
        void UploadVertexData(const void* data, u32 size, u32 offset);

        void SetPredefiniedShape(ref_ptr <Geometry> geo, Geometry::BasicShapes shape);
        void SetPredefiniedMaterial(ref_ptr <Material> mat, Material::BasicMaterials basic_mat);

    protected:
    private:
        ResourceManager();
        ~ResourceManager();

        void StartUp();
        void ShutDown();

        u32 NumberOfIndexBuffer();
        u32 NumberOfVertexBuffer();

        struct ResourceData;
        ResourceData* data_ = nullptr;

    };
}

#endif // __RESOURCE_MANAGER_H__

