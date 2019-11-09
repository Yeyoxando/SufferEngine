#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <common_definitions.h>
#include <data_types.h>

class Scene;

namespace Suffer {

    class ResourceManager {

        friend class SufferManager;

	public:

		struct GPUResource {
		
			GPUResource() {  id_ = 0; type_ = kInvalid; };
			GPUResource(const GPUResource& r) = delete;
			~GPUResource() {};
		
			const Scene* scene_context_;
			s32 id_;
		
			enum ResourceType {
				kIndexBuffer = 0,
				kVertexBuffer,
				kTexture,
				kInvalid
			};
		
			ResourceType type_;
		
		};

        struct IndexBuffer : public GPUResource {

            IndexBuffer() { id_ = -1; };
            ~IndexBuffer() {};

            void Init(u32 size);
            u16 GetIndex(u32 index);

        };

        struct VertexBuffer : public GPUResource {
            
            VertexBuffer() { id_ = -1; };
            ~VertexBuffer() {};

            enum VertexFormat {
                kVertexFormat_3P = 0,
                kVertexFormat_Invalid = 10
            };

            // Don't creates the buffer
            void Init(VertexFormat format, u32 size);
            float GetVertex(u32 index);

        };
        
        void UploadIndexData(const void* data, u32 size, u32 offset);
        void UploadVertexData(const void* data, u32 size, u32 offset);

        //void SetPredefiniedShape(ref_ptr <Geometry> geo, Geometry::BasicShapes shape);
        //void SetPredefiniedMaterial(ref_ptr <Material> mat, Material::BasicMaterials basic_mat);



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

