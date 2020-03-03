/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 27-02-2019
 * Shadow map command Header
 */

#include "shadow_map.h"
#include "suffermanager.h"
#include "internal_resource_manager.h"
#include <gl/glew.h>

struct Suffer::ShadowMap::Data {

  s32 light_framebuffer_id_;

};

// ------------------------------------------------------------------------- //

Suffer::ShadowMap::ShadowMap(){

  cmd_type_ = Command::kCommandType_Render;
  data_ = new Data();

}

// ------------------------------------------------------------------------- //

void Suffer::ShadowMap::SetData(LightComponent* light){

  // TODO: friend class shadow map in lightcomponent
  //data_->light_framebuffer_id_ = light->framebuffer_id_;

}

// ------------------------------------------------------------------------- //

Suffer::ShadowMap::~ShadowMap(){

  if (!data_) return;

  delete data_;
  data_ = nullptr;

}

// ------------------------------------------------------------------------- //

void Suffer::ShadowMap::Execute() const{

  s32 id_frame_buffer = data_->light_framebuffer_id_;

  if (suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].gpu_version_ == 0) {
    glGenFramebuffers(1, &suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].current_gl_framebuffer_);
  }

  if (suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].gpu_version_ < suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].version_) {

    glBindFramebuffer(GL_FRAMEBUFFER, suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].current_gl_framebuffer_);

    // --------------------------- IsTextureCreated -------------------------- //

    {
      // DEPTH TEXTURE
      s32 id_texture = suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].depth_texture_id_;

      if (suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ == 0) {
        glGenTextures(1, &suffer.resource_manager_.data_->internal_textures_[id_texture].current_texture_id_);
      }

      if (suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ < suffer.resource_manager_.data_->internal_textures_[id_texture].version_) {
        glBindTexture(GL_TEXTURE_2D, suffer.resource_manager_.data_->internal_textures_[id_texture].current_texture_id_);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, SHADOW_SIZE, SHADOW_SIZE,
          0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

        // WRAP S
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

        // WRAP T
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // MIN FILTER
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // MAG FILTER
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glGenerateMipmap(GL_TEXTURE_2D);

        suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ = suffer.resource_manager_.data_->internal_textures_[id_texture].version_;
      }

    }

    // --------------------------- IsTextureCreated -------------------------- //


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
      suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].depth_texture_id_].current_texture_id_,
      0);

    // Set both to none, we only want to use the depth texture
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE) {
      printf("FrameBuffer not complete.\n");
      return;
    }

    suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].gpu_version_ = suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].version_;

  }

  glViewport(0, 0, SHADOW_SIZE, SHADOW_SIZE);
  glBindFramebuffer(GL_FRAMEBUFFER, suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].current_gl_framebuffer_);

  //Clear only depth buffer
  glClear(GL_DEPTH_BUFFER_BIT);

  //specific fragment and vertex shader for that

  //Calculate view and projection matrixes and set uniforms



  // --------------------------------- Draw -------------------------------- //

  {

    //u32 number_elements = suffer.resource_manager_.data_->internal_index_buffers_[data_->index_buffer_id_].data_.size();
    //
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_index_buffers_[data_->index_buffer_id_].current_gl_buffer_);
    //
    //glDrawElements(GL_TRIANGLES, number_elements, GL_UNSIGNED_SHORT, (GLvoid*)0);

  }

  // --------------------------------- Draw -------------------------------- //
}

// ------------------------------------------------------------------------- //
