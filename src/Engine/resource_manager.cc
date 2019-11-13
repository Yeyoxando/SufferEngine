// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>


#include "resource_manager.h"
#include "internal_resource_manager.h"
#include "common_definitions.h"
#include "suffermanager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Suffer::ResourceManager::ResourceManager(){

  // Empty

}

// --------------------------------------------------------------//

Suffer::ResourceManager::~ResourceManager(){

  // Empty

}

// --------------------------------------------------------------//

void Suffer::ResourceManager::StartUp() {
  data_ = new ResourceData();

  data_->InitInternalBuffers();
  data_->InitInternalTextures();
  data_->InitInternalMaterials();
}

// --------------------------------------------------------------//

void Suffer::ResourceManager::ShutDown() {
  if (data_ == nullptr) return;
  delete data_;
  data_ = nullptr;

}

// --------------------------------------------------------------//

void Suffer::ResourceManager::UploadVertexData(const ref_ptr<VertexBuffer> buffer, Array<float> *data) {

#ifdef ASSERT
  assert(buffer.get() != nullptr && "Buffer is NULL!");
  assert(buffer.get()->format_ != VertexBuffer::kVertexFormat_Invalid && "Vertex format is INVALID!");
#endif

  data_->internal_vertex_buffers_[buffer->id_].data_.copy(*data);
  data_->internal_vertex_buffers_[buffer->id_].version_++;
  data_->internal_vertex_buffers_[buffer->id_].id_handle_ = buffer->id_;

}

// --------------------------------------------------------------//

void Suffer::ResourceManager::UploadVertexData(const ref_ptr<VertexBuffer> buffer, float* data, u32 size) {

#ifdef ASSERT
  assert(buffer.get() != nullptr && "Buffer is NULL!");
  assert(data != nullptr && "Data is NULL!");
  assert(buffer.get()->format_ != VertexBuffer::kVertexFormat_Invalid && "Vertex format is INVALID!");
#endif

  Array<float> vertices_;
  vertices_.alloc(size);
  for (u32 i = 0; i < size; ++i) {
    vertices_[i] = data[i];
  }

  data_->internal_vertex_buffers_[buffer->id_].data_.copy(vertices_);
  data_->internal_vertex_buffers_[buffer->id_].version_++;
  data_->internal_vertex_buffers_[buffer->id_].id_handle_ = buffer->id_;
}

// --------------------------------------------------------------//

void Suffer::ResourceManager::UploadIndexData(const ref_ptr<IndexBuffer> buffer, Array<u16> *data) {

#ifdef ASSERT
  assert(buffer.get() != nullptr && "Buffer is NULL!");
#endif
  data_->internal_index_buffers_[buffer->id_].data_.copy(*data);
  data_->internal_index_buffers_[buffer->id_].version_++;
  data_->internal_index_buffers_[buffer->id_].id_handle_ = buffer->id_;

}

// --------------------------------------------------------------//

void Suffer::ResourceManager::UploadIndexData(const ref_ptr<IndexBuffer> buffer, u16* data, u32 size) {

#ifdef ASSERT
  assert(buffer.get() != nullptr && "Buffer is NULL!");
  assert(data != nullptr && "Data is NULL!");
#endif

  Array<u16> indices_;
  indices_.alloc(size);
  for (u32 i = 0; i < size; ++i) {
    indices_[i] = data[i];
  }

  data_->internal_index_buffers_[buffer->id_].data_.copy(indices_);
  data_->internal_index_buffers_[buffer->id_].version_++;
  data_->internal_index_buffers_[buffer->id_].id_handle_ = buffer->id_;

}

// --------------------------------------------------------------//

void Suffer::ResourceManager::LoadTextureData(const ref_ptr<Texture> texture, const char * file){

#ifdef ASSERT
  assert(texture.get() != nullptr && "Texture is NULL!");
  assert(file != nullptr && "File is NULL!");
#endif

  unsigned char* data = stbi_load(file,
    (int*)&data_->internal_textures_[texture->id_].width_,
    (int*)&data_->internal_textures_[texture->id_].height_,
    (int*)&data_->internal_textures_[texture->id_].number_channels_, 0);


  data_->internal_textures_[texture->id_].data_.copy(data, data + sizeof(data));

  data_->internal_textures_[texture->id_].version_++;
  data_->internal_textures_[texture->id_].id_handle_ = texture->id_;

}

// --------------------------------------------------------------//

Suffer::ResourceManager::GPUResource::GPUResource() {

  id_ = -1;
  type_ = kInvalid;

}

// --------------------------------------------------------------//

Suffer::ResourceManager::GPUResource::~GPUResource() {

}

// --------------------------------------------------------------//

Suffer::ResourceManager::VertexBuffer::VertexBuffer() {

  type_ = GPUResource::kVertexBuffer;
  format_ = kVertexFormat_Invalid;
  id_ = suffer.resource_manager_.data_->number_of_vertex_buffers_;
  suffer.resource_manager_.data_->number_of_vertex_buffers_++;

}

// --------------------------------------------------------------//

Suffer::ResourceManager::IndexBuffer::IndexBuffer() {

  type_ = GPUResource::kIndexBuffer;
  id_ = suffer.resource_manager_.data_->number_of_index_buffers_;
  suffer.resource_manager_.data_->number_of_index_buffers_++;

}

// --------------------------------------------------------------//

Suffer::ResourceManager::Texture::Texture(){
  type_ = GPUResource::kTexture;
  id_ = suffer.resource_manager_.data_->number_of_textures_;
  suffer.resource_manager_.data_->number_of_textures_++;
}

// --------------------------------------------------------------//

Suffer::ResourceManager::ResourceData::ResourceData(){

}

// --------------------------------------------------------------//

Suffer::ResourceManager::ResourceData::~ResourceData(){

}

// --------------------------------------------------------------//

void Suffer::ResourceManager::ResourceData::InitInternalBuffers() {

  internal_index_buffers_.alloc(MAX_BUFFERS);
  internal_vertex_buffers_.alloc(MAX_BUFFERS);

  number_of_index_buffers_ = 0;
  number_of_vertex_buffers_ = 0;

}

// --------------------------------------------------------------//

void Suffer::ResourceManager::ResourceData::InitInternalTextures() {

  internal_textures_.alloc(MAX_TEXTURES);

  number_of_textures_ = 0;

}

// --------------------------------------------------------------//

void Suffer::ResourceManager::ResourceData::InitInternalMaterials() {
  internal_materials_.alloc(1);

  number_of_materials_ = 0;

  // Default material
  internal_materials_[number_of_materials_].id_handle_ = 0;

  internal_materials_[number_of_materials_].vertex_shader_ = R"VSHADER(
	
	  #version 330
	  layout(location = 0) in vec3 a_position;
	  layout(location = 1) in vec3 a_normal;
    
    uniform mat4 u_m_matrix;
    uniform mat4 u_v_matrix;
    uniform mat4 u_p_matrix;
    
    out vec3 normal;

	  void main(){
      mat4 accum_matrix = u_p_matrix * u_v_matrix * u_m_matrix;
      normal = normalize((accum_matrix * vec4(a_normal, 0.0))).xyz;
		  gl_Position = accum_matrix * vec4(a_position, 1.0f);
	  }

	)VSHADER";

  internal_materials_[number_of_materials_].fragment_shader_ = R"FSHADER(
  
    #version 330

    out vec4 fragColor;
    
    uniform vec4 u_color;
    in vec3 normal;
    vec3 light_dir = vec3(0, 0, 1);
    vec3 light_color = vec3(1, 1, 1);

//---------------------------------------------------------------------------//

vec3 CreateDiffuseLight(vec3 lightPos){

	vec3 norm = normalize(normal);
	float diffs = max(dot(norm, -lightPos), 0.0f);
	vec3 diffuseLight = diffs * vec3(light_color) * 0.4;

	return diffuseLight;
}

//---------------------------------------------------------------------------//

    void main(){

      //Ambient
      vec3 ambient = 0.4 * light_color; // (0, 0.8, 0)
      //Diffuse
      float diff = max(dot(normalize(normal), normalize(-light_dir)), 0.0);
      vec3 test = CreateDiffuseLight(light_dir);
      vec3 colorResult = (ambient + test) * u_color.xyz;

      //vec3 aux = u_color.xyz * (normal * 0.5 + 0.5);
      fragColor = vec4(colorResult, 1.0f);
    }
  	
  )FSHADER";

  number_of_materials_++;
}

// --------------------------------------------------------------//
