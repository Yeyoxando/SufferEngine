// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __INTERNAL_RESOURCE_MANAGER_H__
#define __INTERNAL_RESOURCE_MANAGER_H__

#include "resource_manager.h"
#include "GL/glew.h"

struct Suffer::ResourceManager::ResourceData {
  struct InternalVertexBuffer {

    InternalVertexBuffer() { id_handle_ = -1; version_ = 0; gpu_version_ = 0; };
    ~InternalVertexBuffer() {};

    Array<float> data_;
    s32 id_handle_;
    u32 version_;
    u32 gpu_version_;
    GLuint current_gl_buffer_;

  };

  struct InternalIndexBuffer {

    InternalIndexBuffer() { id_handle_ = -1; version_ = 0; gpu_version_ = 0; };
    ~InternalIndexBuffer() {};

    Array<u16> data_;
    s32 id_handle_;
    u32 version_;
    u32 gpu_version_;
    GLuint current_gl_buffer_;

  };

  struct InternalMaterial {
    InternalMaterial() { id_handle_ = -1; is_created_ = false; };
    ~InternalMaterial() {};

    s32 id_handle_;
    char* vertex_shader_;
    char* fragment_shader_;
    GLuint current_program_;
    GLuint vertex_shader_id_;
    GLuint fragment_shader_id_;
    bool is_created_;
  };

  Array<InternalVertexBuffer> internal_vertex_buffers_;
  Array<InternalIndexBuffer> internal_index_buffers_;
  Array<InternalMaterial> internal_materials_;

  u32 number_of_vertex_buffers_;
  u32 number_of_index_buffers_;
  u32 number_of_materials_;

  void InitInternalBuffers();
  void InitInternalMaterials();

};

#endif //__INTERNAL_RESOURCE_MANAGER_H__