// Diego Ochando Torres <ochandoto@esat-alumni.com>

#include "render_manager.h"
#include "suffermanager.h"
#include "internal_render_manager.h"
#include "internal_resource_manager.h"
#include "draw_geometry.h"
#include "component_geometry.h"
#include "component_material.h"
#include "common_definitions.h"

// ------------------------------------------------------------------------- //

Suffer::RenderManager::RenderManager(){

	// Empty

}

// ------------------------------------------------------------------------- //

Suffer::RenderManager::~RenderManager(){

	// Empty

}

// ------------------------------------------------------------------------- //

void Suffer::RenderManager::StartUp(){

  data_ = new RenderData();

	// Init here instead of constructor and call in engine init
  dls_to_draw_ = 0;

  data_->screen_quad_.alloc();
  data_->draw_quad_command_.alloc();

  // Components
  Suffer::ref_ptr< Suffer::GeometryComponent> geometry_component;
  Suffer::ref_ptr< Suffer::MaterialComponent> material_component;
  Suffer::ref_ptr<Suffer::MaterialComponent::RenderToTextureParams> material_params;

  geometry_component.alloc();
  material_component.alloc();
  material_params.alloc();
  
  geometry_component->CreateGeometryWithShape(GeometryComponent::kBasicShapes_Quad);
  geometry_component->SetDrawMode(GeometryComponent::kDrawMode_Triangles);

  material_component->SetParams(material_params.get());

  data_->screen_quad_->AddComponent(geometry_component.get());
  data_->screen_quad_->AddComponent(material_component.get());

  data_->reference_to_texture_params_ = material_params.get();

}

// ------------------------------------------------------------------------- //

void Suffer::RenderManager::ShutDown() {

	// Init here instead of constructor and call in engine finish
  if (data_ == nullptr) return;
  delete data_;
  data_ = nullptr;

}

// ------------------------------------------------------------------------- //

void Suffer::RenderManager::AddToRenderQueue(DisplayList&& logic_dl, ResourceManager::FrameBuffer* framebuffer){

	dl_mutex_.lock();

	// Moves given DL to current DL with std::move
	if (logic_dl.GetDisplayListType() == DisplayList::kDisplayListType_Render) {
    if (framebuffer != nullptr) {
      logic_dl.frame_buffer_id_ = framebuffer->id_;
    }
    list_of_dl_.push_back(std::move(logic_dl));
    dls_to_draw_++;
	}

	dl_mutex_.unlock();

}

// ------------------------------------------------------------------------- //

void Suffer::RenderManager::DoRender(){
  
  u32 render_buckets = dls_to_draw_;

  // Extract first DisplayList of the list
  for (u32 i = 0; i < render_buckets; ++i) {
    dl_mutex_.lock();

    if (!list_of_dl_.empty())
      render_dl_ = std::move(list_of_dl_.front());

    list_of_dl_.pop_front();

    dls_to_draw_--;

    dl_mutex_.unlock();

    // ---------------------- IsFrameBufferCreated ----------------------- //
    
    {
      
      if (render_dl_.frame_buffer_id_ >= 0) {

        s32 id_frame_buffer = render_dl_.frame_buffer_id_;

        if (suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].gpu_version_ == 0) {
          glGenFramebuffers(1, &suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].current_gl_framebuffer_);
        }
        printf("\nGPU %d", suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].gpu_version_);
        printf("\nnormal %d", suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].version_);
        if (suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].gpu_version_ < suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].version_) {

          glBindFramebuffer(GL_FRAMEBUFFER, suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].current_gl_framebuffer_);

          // --------------------------- IsTextureCreated -------------------------- //

          {
            // COLOR TEXTURE
            s32 id_texture = suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].color_texture_id_;

            if (suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ == 0) {
              glGenTextures(1, &suffer.resource_manager_.data_->internal_textures_[id_texture].current_texture_id_);
              data_->reference_to_texture_params_->albedo_texture_id_ = suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].color_texture_id_;
            }

            if (suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ < suffer.resource_manager_.data_->internal_textures_[id_texture].version_) {
              glBindTexture(GL_TEXTURE_2D, suffer.resource_manager_.data_->internal_textures_[id_texture].current_texture_id_);

              glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                suffer.resource_manager_.data_->internal_textures_[id_texture].width_,
                suffer.resource_manager_.data_->internal_textures_[id_texture].height_,
                0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

              // WRAP S
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

              // WRAP T
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

              // MIN FILTER
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

              // MAG FILTER
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



              glGenerateMipmap(GL_TEXTURE_2D);

              suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ = suffer.resource_manager_.data_->internal_textures_[id_texture].version_;
            }

            // DEPTH TEXTURE
            id_texture = suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].depth_texture_id_;

            if (suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ == 0) {
              glGenTextures(1, &suffer.resource_manager_.data_->internal_textures_[id_texture].current_texture_id_);
            }

            if (suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ < suffer.resource_manager_.data_->internal_textures_[id_texture].version_) {
              glBindTexture(GL_TEXTURE_2D, suffer.resource_manager_.data_->internal_textures_[id_texture].current_texture_id_);

              glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8,
                suffer.resource_manager_.data_->internal_textures_[id_texture].width_,
                suffer.resource_manager_.data_->internal_textures_[id_texture].height_,
                0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

              // WRAP S
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

              // WRAP T
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

              // MIN FILTER
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

              // MAG FILTER
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

              glGenerateMipmap(GL_TEXTURE_2D);

              suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ = suffer.resource_manager_.data_->internal_textures_[id_texture].version_;
            }

          }

          // --------------------------- IsTextureCreated -------------------------- //

          GLenum error;
          glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
            suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].color_texture_id_].current_texture_id_,
            0);
          error = glGetError();

          glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
            suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].depth_texture_id_].current_texture_id_,
            0);
          error = glGetError();

          GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
          assert(status == GL_FRAMEBUFFER_COMPLETE);
          if (status != GL_FRAMEBUFFER_COMPLETE) {
            printf("FrameBuffer not complete.\n");
            return;
          }

          suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].gpu_version_ = suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].version_;
        }
     
        glBindFramebuffer(GL_FRAMEBUFFER, suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].current_gl_framebuffer_);
        glViewport(0, 0, suffer.GetWindowSize().x_, suffer.GetWindowSize().y_);
        
        //Set last framebuffer texture to draw it in imgui
        current_drawn_texture_id_ = suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[id_frame_buffer].color_texture_id_].current_texture_id_;
      
      }

    }

    // ---------------------- IsFrameBufferCreated ----------------------- //


    // Execute the extracted DL
    u32 size = render_dl_.Size();

    for (int i = 0; i < size; ++i) {
      const Command* cmd = render_dl_.dl_commands_[i].get();
      cmd->Execute();
    }


    render_dl_.Clear();

  }
 
  //Set final texture to draw in imgui

  // Render to final framebuffer (screen quad)
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glDisable(GL_DEPTH_TEST);

  data_->draw_quad_command_->SetData(data_->screen_quad_.get());
  data_->draw_quad_command_->Execute();

}

// ------------------------------------------------------------------------- //

//void Suffer::RenderManager::SetFrameBuffer(ResourceManager::FrameBuffer* frame_buffer) {
//
//  assert(frame_buffer != nullptr);
//  if (frame_buffer == nullptr) {
//    printf("NULL FrameBuffer.\n");
//    return;
//  }
//
//  frame_buffer_id_ = frame_buffer->id_;
//
//}

// ------------------------------------------------------------------------- //

Suffer::RenderManager::RenderData::RenderData(){



}

// ------------------------------------------------------------------------- //

Suffer::RenderManager::RenderData::~RenderData(){



}

// ------------------------------------------------------------------------- //
