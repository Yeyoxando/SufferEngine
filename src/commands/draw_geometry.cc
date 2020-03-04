/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Draw Geometry command Header
 */

#include <draw_geometry.h>
#include <gl/glew.h>
#include "time.h"
#include <data_types.h>
#include "scene.h"
#include "vector4.h"
#include "suffermanager.h"
#include "internal_resource_manager.h"
#include "component_geometry.h"
#include "component_material.h"
#include "common_definitions.h"
#include <string>

#define MAX_USED_TEXTURES 5
//14 to uniforms, rest for lights
#define MAX_USED_VEC4DATA 55 

// ------------------------------------------------------------------------- //

struct Suffer::DrawGeometry::Data {

  // Geometry
  s32 vertex_buffer_id_;
  s32 index_buffer_id_;
  GLenum draw_mode_;

  // Contains the model, view and projections matrixes + 1 color Vector4 (13 Vector4 in total)
  float u_data_[MAX_USED_VEC4DATA * 4];

  // Textures has to be separated
  s32 texture_ids_[MAX_USED_TEXTURES];
  u32 current_used_textures_;
  s32 light_texture_ids_[MAX_LIGHTS];
  u32 current_light_used_textures_;

  u32 material_type_;

};

// ------------------------------------------------------------------------- //

Suffer::DrawGeometry::DrawGeometry() {

  cmd_type_ = Command::kCommandType_Render;
  data_ = new Data();
  data_->current_used_textures_ = 0;

  for (u32 i = 0; i < MAX_USED_TEXTURES; ++i) {
    data_->texture_ids_[i] = -1;
  }

  data_->material_type_ = MaterialComponent::kParamsType_Invalid;

}

// ------------------------------------------------------------------------- //

Suffer::DrawGeometry::~DrawGeometry() {

  if (!data_) return;

  delete data_;
  data_ = nullptr;

}

// ------------------------------------------------------------------------- //

void Suffer::DrawGeometry::SetData(GameObject* go) {

  // ---------------------------- SetGeometry ------------------------------ //

  {
  
    auto geometry_component = go->GetComponent(Suffer::Component::kComponentKind_Geometry);
    GeometryComponent* geometry_ = reinterpret_cast<GeometryComponent*>(geometry_component);

    data_->vertex_buffer_id_ = geometry_->vertex_buffer_id_;
    data_->index_buffer_id_ = geometry_->index_buffer_id_;
    Suffer::GeometryComponent::DrawMode mode_ = geometry_->mode_;

    switch (mode_){

        case Suffer::GeometryComponent::kDrawMode_Invalid:
            data_->draw_mode_ = GL_NONE;
            break;
        case Suffer::GeometryComponent::kDrawMode_Triangles:
            data_->draw_mode_ = GL_TRIANGLES;
            break;
        case Suffer::GeometryComponent::kDrawMode_Lines:
            data_->draw_mode_ = GL_LINES;
            break;
        case Suffer::GeometryComponent::kDrawMode_LineLoop:
            data_->draw_mode_ = GL_LINE_LOOP;
            break;
        case Suffer::GeometryComponent::kDrawMode_LineStrip:
            data_->draw_mode_ = GL_LINE_STRIP;
            break;
        case Suffer::GeometryComponent::kDrawMode_Points:
            data_->draw_mode_ = GL_POINTS;
            break;
        case Suffer::GeometryComponent::kDrawMode_Patches:
            data_->draw_mode_ = GL_PATCHES;
        default:
            break;
    }
  
  }

  // ---------------------------- SetGeometry ------------------------------ //


  // --------------------------- StoreUniforms ----------------------------- //

  {

    auto material_component = go->GetComponent(Suffer::Component::kComponentKind_Material);
    MaterialComponent* material_ = reinterpret_cast<MaterialComponent*>(material_component);
    data_->material_type_ = (u32)material_->current_params_->params_type_;

    // -- Common Attributes --
    MaterialComponent::BaseParams* params = material_->current_params_.get();
    mathmorra::Vector4 aux_color = params->color_;
    float values[4] = { aux_color.x_, aux_color.y_, aux_color.z_, aux_color.w_ };

    // Copy color to next free uniform space, after Vector n12 because of 3 matrixes, > u_data[48]
    data_->u_data_[48] = values[0];
    data_->u_data_[49] = values[1];
    data_->u_data_[50] = values[2];
    data_->u_data_[51] = values[3];

    // -- Set specific material parameters --
    switch (data_->material_type_) {
    case MaterialComponent::ParamsType::kParamsType_Default: {
      MaterialComponent::DefaultParams* default_params_;
      default_params_ = reinterpret_cast<MaterialComponent::DefaultParams*>(params);
      data_->u_data_[52] = suffer.GetCurrentScene()->GetMainCamera()->Position()[0];
      data_->u_data_[53] = suffer.GetCurrentScene()->GetMainCamera()->Position()[1];
      data_->u_data_[54] = suffer.GetCurrentScene()->GetMainCamera()->Position()[2];
      data_->u_data_[55] = (float)Time();

      data_->texture_ids_[0] = default_params_->albedo_texture_id_;
      data_->texture_ids_[1] = default_params_->specular_texture_id_;
      data_->current_used_textures_ = 2;
      SetLights();
    }
      break;
    case MaterialComponent::ParamsType::kParamsType_Phong: {
      MaterialComponent::PhongParams* phong_params_;
      phong_params_ = reinterpret_cast<MaterialComponent::PhongParams*>(params);
      data_->u_data_[52] = suffer.GetCurrentScene()->GetMainCamera()->Position()[0];
      data_->u_data_[53] = suffer.GetCurrentScene()->GetMainCamera()->Position()[1];
      data_->u_data_[54] = suffer.GetCurrentScene()->GetMainCamera()->Position()[2];
      data_->u_data_[55] = (float)Time();

      data_->current_used_textures_ = 0;
      SetLights();
    }
      break;
    case MaterialComponent::ParamsType::kParamsType_RenderToTexture: {
      MaterialComponent::RenderToTextureParams* render_params_;
      render_params_ = reinterpret_cast<MaterialComponent::RenderToTextureParams*>(params);

      data_->texture_ids_[0] = render_params_->albedo_texture_id_;
      data_->current_used_textures_ = 1;
    }
      break;
    case MaterialComponent::ParamsType::kParamsType_Invalid:
      assert(data_->material_type_ != MaterialComponent::kParamsType_Invalid && "Material type not set");
      break;
    default:
      break;
    }

  }

  // --------------------------- StoreUniforms ----------------------------- //

}

// ------------------------------------------------------------------------- //

void Suffer::DrawGeometry::SetModelMatrix(mathmorra::Matrix4 model) {

  // Model will be in u_data[0] to u_data[3]
  for (u32 i = 0; i < 16; ++i) {
    data_->u_data_[i] = model.m[i];
  }

}

// ------------------------------------------------------------------------- //

void Suffer::DrawGeometry::SetViewMatrix(mathmorra::Matrix4 view) {

  // View will be in u_data[4] to u_data[7]
  for (u32 i = 0; i < 16; ++i) {
    data_->u_data_[i + 16] = view.m[i];
  }

}

// ------------------------------------------------------------------------- //

void Suffer::DrawGeometry::SetProjectionMatrix(mathmorra::Matrix4 projection) {

  // Projection will be in u_data[8] to u_data[11]
  for (u32 i = 0; i < 16; ++i) {
    data_->u_data_[i + 32] = projection.m[i];
  }

}

// ------------------------------------------------------------------------- //

void Suffer::DrawGeometry::SetLights(){

  LightManager::DirectionalLight* light_for_shadow = suffer.light_manager_.lights_[0].get();
  
  for (u32 i = 0; i < 16; ++i) {
    data_->u_data_[60 + i] = light_for_shadow->view_mat_.m[i];
    data_->u_data_[76 + i] = light_for_shadow->projection_mat_.m[i];
  }

  u32 start = 92;
  // Lighting
  u32 number_lights = 0;
  u32 offset = 0;
  u32 current_lights = suffer.light_manager_.current_lights_;
  for (u32 i = 0; i < current_lights; ++i) {
    LightManager::DirectionalLight* light = suffer.light_manager_.lights_[i].get();
    if (light->Active()) {
      number_lights++;
      LightManager::PointLight* point_light;
      LightManager::SpotLight* spot_light;
      switch (light->GetLightKind()) {
      case LightManager::kLightKind_Directional: {
        //20
        data_->u_data_[start + 0  + (offset)] = light->Direction()[0];
        data_->u_data_[start + 1  + (offset)] = light->Direction()[1];
        data_->u_data_[start + 2  + (offset)] = light->Direction()[2];
        data_->u_data_[start + 3  + (offset)] = (float)light->Active();
        data_->u_data_[start + 4  + (offset)] = light->Color()[0];
        data_->u_data_[start + 5  + (offset)] = light->Color()[1];
        data_->u_data_[start + 6  + (offset)] = light->Color()[2];
        data_->u_data_[start + 7  + (offset)] = light->GetLightKind();
        data_->u_data_[start + 8  + (offset)] = light->Ambient()[0];
        data_->u_data_[start + 9  + (offset)] = light->Ambient()[1];
        data_->u_data_[start + 10 + (offset)] = light->Ambient()[2];
        data_->u_data_[start + 11 + (offset)] = light->Intensity();
        data_->u_data_[start + 12 + (offset)] = light->Diffuse()[0];
        data_->u_data_[start + 13 + (offset)] = light->Diffuse()[1];
        data_->u_data_[start + 14 + (offset)] = light->Diffuse()[2];
        data_->u_data_[start + 16 + (offset)] = light->Specular()[0];
        data_->u_data_[start + 17 + (offset)] = light->Specular()[1];
        data_->u_data_[start + 18 + (offset)] = light->Specular()[2];
        offset += 20;
      }
        break;
      case LightManager::kLightKind_Point: {
        //24
        point_light = static_cast<LightManager::PointLight*>(light);
        data_->u_data_[start + 0  + (offset)] = point_light->Position()[0];
        data_->u_data_[start + 1  + (offset)] = point_light->Position()[1];
        data_->u_data_[start + 2  + (offset)] = point_light->Position()[2];
        data_->u_data_[start + 3  + (offset)] = (float)light->Active();
        data_->u_data_[start + 4  + (offset)] = point_light->Color()[0];
        data_->u_data_[start + 5  + (offset)] = point_light->Color()[1];
        data_->u_data_[start + 6  + (offset)] = point_light->Color()[2];
        data_->u_data_[start + 7  + (offset)] = light->GetLightKind();
        data_->u_data_[start + 8  + (offset)] = point_light->Ambient()[0];
        data_->u_data_[start + 9  + (offset)] = point_light->Ambient()[1];
        data_->u_data_[start + 10 + (offset)] = point_light->Ambient()[2];
        data_->u_data_[start + 11 + (offset)] = point_light->Intensity();
        data_->u_data_[start + 12 + (offset)] = point_light->Diffuse()[0];
        data_->u_data_[start + 13 + (offset)] = point_light->Diffuse()[1];
        data_->u_data_[start + 14 + (offset)] = point_light->Diffuse()[2];
        data_->u_data_[start + 16 + (offset)] = point_light->Specular()[0];
        data_->u_data_[start + 17 + (offset)] = point_light->Specular()[1];
        data_->u_data_[start + 18 + (offset)] = point_light->Specular()[2];
        data_->u_data_[start + 20 + (offset)] = point_light->Constant();
        data_->u_data_[start + 21 + (offset)] = point_light->Linear();
        data_->u_data_[start + 22 + (offset)] = point_light->Quadratic();
        offset += 24;
      }
        break;
      case LightManager::kLightKind_Spot: {
        //32
        spot_light = static_cast<LightManager::SpotLight*>(light);
        data_->u_data_[start + 0  + (offset)] = spot_light->Direction()[0];
        data_->u_data_[start + 1  + (offset)] = spot_light->Direction()[1];
        data_->u_data_[start + 2  + (offset)] = spot_light->Direction()[2];
        data_->u_data_[start + 3  + (offset)] = (float)light->Active();
        data_->u_data_[start + 4  + (offset)] = spot_light->Position()[0];
        data_->u_data_[start + 5  + (offset)] = spot_light->Position()[1];
        data_->u_data_[start + 6  + (offset)] = spot_light->Position()[2];
        data_->u_data_[start + 7  + (offset)] = light->GetLightKind();
        data_->u_data_[start + 8  + (offset)] = spot_light->Color()[0];
        data_->u_data_[start + 9  + (offset)] = spot_light->Color()[1];
        data_->u_data_[start + 10 + (offset)] = spot_light->Color()[2];
        data_->u_data_[start + 12 + (offset)] = spot_light->Ambient()[0];
        data_->u_data_[start + 13 + (offset)] = spot_light->Ambient()[1];
        data_->u_data_[start + 14 + (offset)] = spot_light->Ambient()[2];
        data_->u_data_[start + 15 + (offset)] = spot_light->Intensity();
        data_->u_data_[start + 16 + (offset)] = spot_light->Diffuse()[0];
        data_->u_data_[start + 17 + (offset)] = spot_light->Diffuse()[1];
        data_->u_data_[start + 18 + (offset)] = spot_light->Diffuse()[2];
        data_->u_data_[start + 20 + (offset)] = spot_light->Specular()[0];
        data_->u_data_[start + 21 + (offset)] = spot_light->Specular()[1];
        data_->u_data_[start + 22 + (offset)] = spot_light->Specular()[2];
        data_->u_data_[start + 24 + (offset)] = spot_light->Constant();
        data_->u_data_[start + 25 + (offset)] = spot_light->Linear();
        data_->u_data_[start + 26 + (offset)] = spot_light->Quadratic();
        data_->u_data_[start + 28 + (offset)] = spot_light->CutOff();
        data_->u_data_[start + 29 + (offset)] = spot_light->OuterCutOff();
        offset += 32;
      }
        break;
      case LightManager::kLightKind_Invalid:

        break;
      default:
        break;
      }
      
    }

  }

  data_->light_texture_ids_[0] = suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_light_frame_buffers_[0].depth_texture_id_].current_texture_id_;
  data_->current_light_used_textures_ = 1;

  data_->u_data_[56] = number_lights;

}

void Suffer::DrawGeometry::Execute() const {

  GLenum error;
  
  // ---------------------- IsBufferCreated (Vertex) ----------------------- //

  {

    assert(data_->vertex_buffer_id_ >= 0);

    if (data_->vertex_buffer_id_ < 0) return;

    s32 id_vertex = data_->vertex_buffer_id_;

    if (suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].gpu_version_ == 0) {
      glGenBuffers(1, &suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);
    }

    if (suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].gpu_version_ < suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].version_) {
      glBindBuffer(GL_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);

      glBufferData(GL_ARRAY_BUFFER,
        suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].data_.sizeInBytes(),
        suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].data_.get(),
        GL_STATIC_DRAW);

      suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].gpu_version_ = suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].version_;
    }

  }

  // ---------------------- IsBufferCreated (Vertex) ----------------------- //

  // ----------------------------------------------------------------------- //

  // ----------------------- IsBufferCreated (Index) ----------------------- //

  {
  
    assert(data_->index_buffer_id_ >= 0);

    if (data_->index_buffer_id_ < 0) return;
    s32 id_index = data_->index_buffer_id_;
    if (suffer.resource_manager_.data_->internal_index_buffers_[id_index].gpu_version_ == 0) {
      glGenBuffers(1, &suffer.resource_manager_.data_->internal_index_buffers_[id_index].current_gl_buffer_);
    }

    if (suffer.resource_manager_.data_->internal_index_buffers_[id_index].gpu_version_ < suffer.resource_manager_.data_->internal_index_buffers_[id_index].version_) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_index_buffers_[id_index].current_gl_buffer_);

      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        suffer.resource_manager_.data_->internal_index_buffers_[id_index].data_.sizeInBytes(),
        suffer.resource_manager_.data_->internal_index_buffers_[id_index].data_.get(),
        GL_STATIC_DRAW);

      suffer.resource_manager_.data_->internal_index_buffers_[id_index].gpu_version_ = suffer.resource_manager_.data_->internal_index_buffers_[id_index].version_;
    }

  }

  // ----------------------- IsBufferCreated (Index) ----------------------- //

  // ----------------------------------------------------------------------- //

  // --------------------------- IsTextureCreated -------------------------- //

  {

    for (u32 i = 0; i < data_->current_used_textures_; ++i) {

      if (data_->texture_ids_[i] < 0) return;
      s32 id_texture = data_->texture_ids_[i];

      if (suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ == 0) {
        glGenTextures(1, &suffer.resource_manager_.data_->internal_textures_[id_texture].current_texture_id_);
      }

      if (suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ < suffer.resource_manager_.data_->internal_textures_[id_texture].version_) {
        glBindTexture(GL_TEXTURE_2D, suffer.resource_manager_.data_->internal_textures_[id_texture].current_texture_id_);

        // WRAP S
        switch (suffer.resource_manager_.data_->internal_textures_[id_texture].wrap_s_) {
        case ResourceManager::Texture::kTextureWrap_Repeat:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          break;
        case ResourceManager::Texture::kTextureWrap_MirroredRepeat:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
          break;
        case ResourceManager::Texture::kTextureWrap_ClampToEdge:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          break;
        default:
          break;
        }

        // WRAP T
        switch (suffer.resource_manager_.data_->internal_textures_[id_texture].wrap_t_) {
        case ResourceManager::Texture::kTextureWrap_Repeat:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          break;
        case ResourceManager::Texture::kTextureWrap_MirroredRepeat:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
          break;
        case ResourceManager::Texture::kTextureWrap_ClampToEdge:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
          break;
        default:
          break;
        }

        // MIN FILTER
        switch (suffer.resource_manager_.data_->internal_textures_[id_texture].min_filter_) {
        case ResourceManager::Texture::kTextureFilter_Linear:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          break;
        case ResourceManager::Texture::kTextureFilter_Nearest:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
          break;
        default:
          break;
        }

        // MAG FILTER
        switch (suffer.resource_manager_.data_->internal_textures_[id_texture].mag_filter_) {
        case ResourceManager::Texture::kTextureFilter_Linear:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          break;
        case ResourceManager::Texture::kTextureFilter_Nearest:
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          break;
        default:
          break;
        }

        // UPLOAD DATA DEPENDING ON NUMBER CHANNELS
        switch (suffer.resource_manager_.data_->internal_textures_[id_texture].number_channels_) {
        case 3:
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
            suffer.resource_manager_.data_->internal_textures_[id_texture].width_,
            suffer.resource_manager_.data_->internal_textures_[id_texture].height_,
            0, GL_RGB, GL_UNSIGNED_BYTE,
            suffer.resource_manager_.data_->internal_textures_[id_texture].data_.get());
          break;
        case 4:
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            suffer.resource_manager_.data_->internal_textures_[id_texture].width_,
            suffer.resource_manager_.data_->internal_textures_[id_texture].height_,
            0, GL_RGBA, GL_UNSIGNED_BYTE,
            suffer.resource_manager_.data_->internal_textures_[id_texture].data_.get());
          break;
        default:
          assert(1 && "\n Not contemplated number of channels.");
          break;
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ = suffer.resource_manager_.data_->internal_textures_[id_texture].version_;
      }
    
    }

  }

  // --------------------------- IsTextureCreated -------------------------- //

  // ----------------------------------------------------------------------- //

  // -------------------------- IsMaterialCreated -------------------------- //

  {
  
    u32 mat_type = data_->material_type_;

    // If internal material is not created, creates it
    if (!suffer.resource_manager_.data_->internal_materials_[mat_type].is_created_) {
      // Create vertex shader
      suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_ =
        glCreateShader(GL_VERTEX_SHADER);

      // Create fragment shader
      suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_ =
        glCreateShader(GL_FRAGMENT_SHADER);

      // Get shaders length
      const GLint vertex_size = strlen(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_);
      const GLint fragment_size = strlen(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_);

      // Upload vertex shader data
      glShaderSource(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_,
        1, &suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_,
        &vertex_size);

      // Upload fragment shader data
      glShaderSource(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_,
        1, &suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_, &fragment_size);
      
      // Compile vertex shader
      glCompileShader(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_);
      
      GLint status = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_, GL_COMPILE_STATUS, &status);
      GLint log_length = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
      Array<char> info_log;
      info_log.alloc(log_length + 1);
      info_log[log_length] = '\0';
      glGetShaderInfoLog(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_, log_length, &log_length, &info_log[0]);

      printf("\n\n%s", info_log.get());
      if (status == GL_FALSE)
        printf("\nERROR: vertex shader not compiled");

      // Compile fragment shader
      glCompileShader(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_);
      status = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_, GL_COMPILE_STATUS, &status);
      log_length = 0;
      info_log.release();
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
      info_log.alloc(log_length + 1);
      info_log[log_length] = '\0';
      glGetShaderInfoLog(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_, log_length, &log_length, &info_log[0]);
      printf("\n\n%s", info_log.get());
      if (status == GL_FALSE)
        printf("\nERROR: fragment shader not compiled");
      info_log.release();


      // Create program
      suffer.resource_manager_.data_->internal_materials_[mat_type].current_program_ = glCreateProgram();
      
      // Attach shaders
      glAttachShader(suffer.resource_manager_.data_->internal_materials_[mat_type].current_program_,
        suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_);
      
      glAttachShader(suffer.resource_manager_.data_->internal_materials_[mat_type].current_program_,
        suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_);
      
      // Link program
      glLinkProgram(suffer.resource_manager_.data_->internal_materials_[mat_type].current_program_);
      
      // Mark internal material as created
      suffer.resource_manager_.data_->internal_materials_[mat_type].is_created_ = true;
    }

  }

  // -------------------------- IsMaterialCreated -------------------------- //

  // ----------------------------------------------------------------------- //

  // ------------------------------- Uniforms ------------------------------ //

  u32 program_id = suffer.resource_manager_.data_->internal_materials_[data_->material_type_].current_program_;

  {

    glUseProgram(program_id);
    
    s32 u_pos = -1;

    // -- Uniform Block --
    u_pos = glGetUniformLocation(program_id, "u_data");
    if (u_pos < 0) {
      printf("\nERROR: u_data uniform not exists.\n");
      //return;
    }

    glUniform4fv(u_pos, MAX_USED_VEC4DATA, data_->u_data_);
    u_pos = -1;
  


    // -- Textures --
    std::string base_tex_name = "u_tex";
    u32 used_textures = 0;

    for (int i = 0; i < data_->current_used_textures_; ++i) {
      
      std::string tex_name = base_tex_name + std::to_string(i);
      const char* str = tex_name.c_str();
      u_pos = glGetUniformLocation(program_id, str);
      if (u_pos < 0) {
        printf("\nERROR: texture %d uniform not exists.", i);
        //return;
      }

      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, suffer.resource_manager_.data_->internal_textures_[data_->texture_ids_[i]].current_texture_id_);

      glUniform1i(u_pos, i);
      u_pos = -1;
      
      used_textures++;

    }

    // -- LightTextures --
    base_tex_name = "u_light_tex";

    for (int i = 0; i < data_->current_light_used_textures_; ++i) {

      std::string tex_name = base_tex_name + std::to_string(i);
      const char* str = tex_name.c_str();
      u_pos = glGetUniformLocation(program_id, str);
      if (u_pos < 0) {
        printf("\nERROR: light texture %d uniform not exists.", i);
        //return;
      }

      glActiveTexture(GL_TEXTURE0 + i + used_textures);
      glBindTexture(GL_TEXTURE_2D, data_->light_texture_ids_[i]);

      glUniform1i(u_pos, i + used_textures);
      u_pos = -1;

    }

  }

  // ------------------------------- Uniforms ------------------------------ //

  // ----------------------------------------------------------------------- //

  // --------------------------- Vertex Attributes ------------------------- //

  {

    glBindBuffer(GL_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_vertex_buffers_[data_->vertex_buffer_id_].current_gl_buffer_);
    auto type = suffer.resource_manager_.data_->internal_vertex_buffers_[data_->vertex_buffer_id_].vertex_format_;
    switch (type) {
    case Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P:
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
      break;
    case Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P_3N:
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (GLvoid*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (GLvoid*)(3 * sizeof(float)));
      break;
    case Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P_3N_2UV:
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)(3 * sizeof(float)));
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)(6 * sizeof(float)));

      break;
    default:

      break;
    }
  
  }

  // --------------------------- Vertex Attributes ------------------------- //

  // ----------------------------------------------------------------------- //

  // --------------------------------- Draw -------------------------------- //

  {

    u32 number_elements = suffer.resource_manager_.data_->internal_index_buffers_[data_->index_buffer_id_].data_.size();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_index_buffers_[data_->index_buffer_id_].current_gl_buffer_);
    
    glDrawElements(data_->draw_mode_, number_elements, GL_UNSIGNED_SHORT, (GLvoid*)0);
    
  }

  // --------------------------------- Draw -------------------------------- //

}

// --------------------------------------------------- //
