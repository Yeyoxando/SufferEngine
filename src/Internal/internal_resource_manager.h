// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __INTERNAL_RESOURCE_MANAGER_H__
#define __INTERNAL_RESOURCE_MANAGER_H__

#include "resource_manager.h"
#include "GL/glew.h"

// ------------------------------------------------------------------------- //

struct Suffer::ResourceManager::ResourceData {
  ResourceData();
  ~ResourceData();

  struct InternalFrameBuffer {
    
    InternalFrameBuffer() { id_handle_ = -1; version_ = 0; gpu_version_ = 0; };
    ~InternalFrameBuffer() {}

    s32 id_handle_;
    u32 version_;
    u32 gpu_version_;
    GLuint current_gl_framebuffer_;

    u16 width_;
    u16 height_;

    s32 color_texture_id_;
    s32 depth_texture_id_;

  };

  struct InternalVertexBuffer {

    InternalVertexBuffer() { id_handle_ = -1; version_ = 0; gpu_version_ = 0; };
    ~InternalVertexBuffer() {};

    Array<float> data_;
    s32 id_handle_;
    s32 vertex_format_;
    u32 version_;
    u32 gpu_version_;
    GLuint current_gl_buffer_;
    GLenum draw_mode_;

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

  struct InternalTexture {

    InternalTexture() { id_handle_ = -1; version_ = 0; gpu_version_ = 0; };
    ~InternalTexture() {};

    Array<u8> data_;
    s32 id_handle_;
    u32 version_;
    u32 gpu_version_;

    u32 width_;
    u32 height_;
    u32 number_channels_;
    Texture::TextureWrap wrap_s_;
    Texture::TextureWrap wrap_t_;
    Texture::TextureFilter min_filter_;
    Texture::TextureFilter mag_filter_;
    GLuint current_texture_id_;

  };

  struct InternalMaterial {
    InternalMaterial() { id_handle_ = -1; is_created_ = false; };
    ~InternalMaterial() {};

    s32 id_handle_;
    const char* vertex_shader_;
    const char* fragment_shader_;
    GLuint current_program_;
    GLuint vertex_shader_id_;
    GLuint fragment_shader_id_;
    bool is_created_;

  };

  Array<InternalVertexBuffer> internal_vertex_buffers_;
  Array<InternalIndexBuffer> internal_index_buffers_;
  Array<InternalTexture> internal_textures_;
  Array<InternalMaterial> internal_materials_;
  Array<InternalFrameBuffer> internal_frame_buffers_;

  u32 number_of_vertex_buffers_;
  u32 number_of_index_buffers_;
  u32 number_of_textures_;
  u32 number_of_materials_;
  u32 number_of_frame_buffers_;

  void InitInternalBuffers();
  void InitInternalMaterials();
  void InitInternalTextures();
  void InitInternalFrameBuffers();

};

// ------------------------------------------------------------------------- //

#endif //__INTERNAL_RESOURCE_MANAGER_H__