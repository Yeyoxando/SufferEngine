/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 03-11-2020
* ShadowCubemap Source
*/

#include "shadow_cubemap.h"
#include "suffermanager.h"
#include "internal_resource_manager.h"
#include <gl/glew.h>

// ------------------------------------------------------------------------- //

struct Suffer::ShadowCubemap::Data {

  s32 light_framebuffer_id_;

};

// ------------------------------------------------------------------------- //

Suffer::ShadowCubemap::ShadowCubemap(){

  cmd_type_ = Command::kCommandType_Render;
  data_ = new Data();

}

// ------------------------------------------------------------------------- //

void Suffer::ShadowCubemap::SetData(LightComponent* light){

  data_->light_framebuffer_id_ = light->reference_->framebuffer_id_;

}

// ------------------------------------------------------------------------- //

Suffer::ShadowCubemap::~ShadowCubemap(){

  if (!data_) return;

  delete data_;
  data_ = nullptr;

}

// ------------------------------------------------------------------------- //

void Suffer::ShadowCubemap::Execute() const{

  s32 id_frame_buffer = data_->light_framebuffer_id_;

  if (suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].gpu_version_ == 0) {
    glGenFramebuffers(1, &suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].current_gl_framebuffer_);
  }

  if (suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].gpu_version_ < suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].version_) {

    //glBindFramebuffer(GL_FRAMEBUFFER, suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].current_gl_framebuffer_);

    // --------------------------- IsTextureCreated -------------------------- //
    
    auto d = suffer.resource_manager_.data_->internal_cubemaps_[0].current_texture_id_;
    s32 id_texture = suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].depth_texture_id_;

    {
      // DEPTH TEXTURE

      if (suffer.resource_manager_.data_->internal_cubemaps_[id_texture].gpu_version_ == 0) {
          glGenTextures(1, &suffer.resource_manager_.data_->internal_cubemaps_[id_texture].current_texture_id_);
      }

      if (suffer.resource_manager_.data_->internal_cubemaps_[id_texture].gpu_version_ < suffer.resource_manager_.data_->internal_cubemaps_[id_texture].version_) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, suffer.resource_manager_.data_->internal_cubemaps_[id_texture].current_texture_id_);
       
        for (u8 i = 0; i < 6; ++i) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_SIZE, SHADOW_SIZE,
              0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        suffer.resource_manager_.data_->internal_cubemaps_[id_texture].gpu_version_ = suffer.resource_manager_.data_->internal_cubemaps_[id_texture].version_;
      }

    }

    // --------------------------- IsTextureCreated -------------------------- //

    glBindFramebuffer(GL_FRAMEBUFFER, suffer.resource_manager_.data_->internal_light_frame_buffers_[id_frame_buffer].current_gl_framebuffer_);
    
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, suffer.resource_manager_.data_->internal_cubemaps_[id_texture].current_texture_id_, 0);

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

}

// ------------------------------------------------------------------------- //
