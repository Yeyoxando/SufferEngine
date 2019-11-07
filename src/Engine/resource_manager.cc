
#include <resource_manager.h>
#include <scoped_array.h>

struct Suffer::ResourceManager::ResourceData {

    struct InternalVertexBuffer {
        InternalVertexBuffer() {};
        Array<float> data_;
        u32 id_handle_;
        u32 version_;
        u32 gpu_version_;

    };

    struct InternalIndexBuffer {
        InternalIndexBuffer() {};
        Array<u16> data_;
        u32 id_handle_;
        u32 version_;
        u32 gpu_version_;

    };

    void Init();

    Array<InternalIndexBuffer> internal_index_buffers_;
    Array<InternalVertexBuffer> internal_vertex_buffers_;

};

void Suffer::ResourceManager::ResourceData::Init(){

    internal_index_buffers_.alloc(MAX_BUFFERS);
    internal_vertex_buffers_.alloc(MAX_BUFFERS);

    u32 size = sizeof(internal_vertex_buffers_[0].data_);
    u32 size2 = sizeof(u16);

}

Suffer::ResourceManager::ResourceManager(){
    data_ = new ResourceData();
}

Suffer::ResourceManager::~ResourceManager(){
    if (data_ == nullptr) return;
    delete data_;
    data_ = nullptr;
}

void Suffer::ResourceManager::StartUp(){
    data_->Init();
}

void Suffer::ResourceManager::ShutDown(){

}

void Suffer::ResourceManager::VertexBuffer::Init(VertexFormat format, u32 size){

}

void Suffer::ResourceManager::VertexBuffer::GetVertex(u16 index){
    
}
