#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <common_definitions.h>
#include <data_types.h>

namespace Suffer {

    class ResourceManager {

        friend class SufferManager;

    public:

        struct IndexBuffer {

            s32 id_;

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
            void GetVertex(u16 index);


            s32 id_;

        };

    protected:
    private:
        ResourceManager();
        ~ResourceManager();

        void StartUp();
        void ShutDown();

        struct ResourceData;
        ResourceData* data_ = nullptr;

    };
}

#endif // __RESOURCE_MANAGER_H__

