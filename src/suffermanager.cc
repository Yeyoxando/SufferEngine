#include "suffermanager.h"
#include "imgui.h"
#include "input.h"
#include "window.h"
#include "imgui_impl_opengl3.h"
#include "interface.h"
#include "common_definitions.h"
#include "time.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "scene.h"

// --------------------------------------------------------------//

struct Suffer::SufferManager::Data {

	Suffer::Window wind_;
	double previous_time_;
	double current_time_;
	double delta_time_;
	Interface interface_;

	ref_ptr<Scene> scene_context_;

	// Mutexes
  Mutex audio_mutex;
  Mutex render_mutex;

	// Running
	bool window_should_close_;



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

// --------------------------------------------------------------//

void Suffer::SufferManager::Data::InitInternalBuffers(){

    internal_index_buffers_.alloc(MAX_BUFFERS);
    internal_vertex_buffers_.alloc(MAX_BUFFERS);

    number_of_index_buffers_ = 0;
    number_of_vertex_buffers_ = 0;

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Data::InitInternalMaterials(){
  internal_materials_.alloc(1);

  // Default material
  internal_materials_[number_of_materials_].id_handle_ = 0;

  internal_materials_[number_of_materials_].vertex_shader_ = R"VSHADER(
	
	  #version 330
	  layout(location = 0) in vec3 a_position;

	  void main(){
		  gl_Position = vec4(a_position, 1.0f);
	  }

	)VSHADER";

  internal_materials_[number_of_materials_].fragment_shader_ = R"FSHADER(
  
  	#version 330
  
  	void main(){
  		gl_FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
  	}
  	
  )FSHADER";

  //strncpy(internal_materials_[number_of_materials_].vertex_shader_, vertex_shader, sizeof(vertex_shader));
  //strncpy(internal_materials_[number_of_materials_].fragment_shader_, fragment_shader, sizeof(fragment_shader));

  //internal_materials_[number_of_materials_].vertex_shader_ = vertex_shader;
  //internal_materials_[number_of_materials_].fragment_shader_ = fragment_shader;

  number_of_materials_++;
}

// --------------------------------------------------------------//

//void SufferManager::Data::InternalGeometry::CreateGeometry(Geometry::BasicShapes shape){
//	switch (shape) {
//	case Geometry::kBasicShapes_Triangle: {
//		// BUFFERS
//		float vertices[] = {
//			0.0f,  0.5f, -1.0f,
//			0.5f, -0.5f, -1.0f,
//			-0.5f, -0.5f, -1.0f
//		};
//
//		glGenBuffers(1, &vertices_ID);
//		glBindBuffer(GL_ARRAY_BUFFER, vertices_ID);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		unsigned char indices[]{ 0, 2, 1 };
//
//		glGenBuffers(1, &indices_ID);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_ID);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//		number_elements = 3;
//
//		break;
//	}
//	case Geometry::kBasicShapes_Quad: {
//
//		// BUFFERS
//		float vertices[] = {
//			0.5f, -0.5f, -1.0f,
//			0.5f,  0.5f, -1.0f,
//		   -0.5f,  0.5f, -1.0f,
//		   -0.5f, -0.5f, -1.0f,
//		};
//
//		glGenBuffers(1, &vertices_ID);
//		glBindBuffer(GL_ARRAY_BUFFER, vertices_ID);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		unsigned char indices[]{ 0, 2, 1, 
//								 2, 3, 0 };
//
//		glGenBuffers(1, &indices_ID);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_ID);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//		number_elements = 6;
//
//		break;
//
//	}
//	case Geometry::kBasicShapes_Cube: {
//
//		// BUFFERS
//		float vertices[] = {
//			// front
//			-0.5, -0.5,  0.5,
//			 0.5, -0.5,  0.5,
//			 0.5,  0.5,  0.5,
//			-0.5,  0.5,  0.5,
//			// back
//			-0.5, -0.5, -0.5,
//			 0.5, -0.5, -0.5,
//			 0.5,  0.5, -0.5,
//			-0.5,  0.5, -0.5
//		};
//
//		glGenBuffers(1, &vertices_ID);
//		glBindBuffer(GL_ARRAY_BUFFER, vertices_ID);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		unsigned char indices[]{ 		
//			// front
//			0, 1, 2,
//			2, 3, 0,
//			// right
//			1, 5, 6,
//			6, 2, 1,
//			// back
//			7, 6, 5,
//			5, 4, 7,
//			// left
//			4, 0, 3,
//			3, 7, 4,
//			// bottom
//			4, 5, 1,
//			1, 0, 4,
//			// top
//			3, 2, 6,
//			6, 7, 3 
//		};
//
//		glGenBuffers(1, &indices_ID);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_ID);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//		number_elements = 36;
//
//		break;
//	}
//	case Geometry::kBasicShapes_NONE:
//		break;
//	default:
//		break;
//	}
//
//}
//
//// --------------------------------------------------------------//
//
//void SufferManager::Data::InternalMaterial::CreateMaterial(Material::BasicMaterials material) {
//	switch (material) {
//	case Material::kBasicMaterials_Default: {
//		// DEFAULT SHADERS
//		
//
//		// HELLO TRIANGLE STUFF -> TODO: THIS WILL BE DELETED
//		GLenum error = glGetError();
//		
//		
//		break;
//	}
//	case Material::kBasicMaterials_NONE: {
//		break;
//	}
//	default:
//		break;
//	}
//
//}

// --------------------------------------------------------------//

Suffer::SufferManager::SufferManager(){

	data_ = new Data();
	data_->scene_context_.alloc();

}

// --------------------------------------------------------------//

Suffer::SufferManager::~SufferManager(){
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------------------//

Suffer::SufferManager::SufferManager(const SufferManager&){

}

// --------------------------------------------------------------//

Suffer::SufferManager& Suffer::SufferManager::instance() {

	static SufferManager* instance = new SufferManager();
	return *instance;

}

// --------------------------------------------------------------//

bool Suffer::SufferManager::Init(){

#ifdef ASSERT
	assert(data_ && "\n Data is null.");
#endif // ASSERT

	data_->wind_.init(800, 600);
	Suffer::InitInput();
	data_->interface_.Init();

	//Subsystems init
	render_manager_.StartUp();


	// Threads Allocation
	logic_.alloc();
	input_.alloc();
	audio_.alloc();

	// Threads Function Assignment
	auto audio_thread = [] { SufferManager::instance().Audio(); };
	audio_.get()->NewTask(audio_thread);

	auto update_thread = [] { SufferManager::instance().Update(); };
	logic_.get()->NewTask(update_thread);

	auto input_thread = [] { SufferManager::instance().Input(); };
	input_.get()->NewTask(input_thread);


	data_->InitInternalBuffers();
	data_->InitInternalMaterials();

	data_->window_should_close_ = false;

	data_->scene_context_->Init();

	//newSong.alloc();

	return true;
}

// --------------------------------------------------------------//

void Suffer::SufferManager::Update() {

	while(1){
		Step(data_->delta_time_);
		logic_->Sleep();
	}

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Draw() {

	//data_->interface_.Update();
	//data_->interface_.Render();

	render_manager_.DoRender();

	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	data_->wind_.swapBuffers();

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Input() {

	while (1) {
		input_->Sleep();

		// Window Should Close
		if (Suffer::IsKeyDown(k_Escape)) {
			data_->window_should_close_ = true;
		}
	}

}

// --------------------------------------------------------------//

bool Suffer::SufferManager::Run(){

	while (!data_->window_should_close_) {

		data_->current_time_ = Suffer::RawTime();
		data_->wind_.processEvents();
		
		input_->Awake();
		
    logic_->Awake();

		Draw();
    
    logic_->WaitMe();

		data_->delta_time_ = (data_->current_time_ - data_->previous_time_) * 0.0001f;
		data_->previous_time_ = data_->current_time_;

	}

	return true;

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Audio() {

	while (1) {

		audio_->Sleep();

		if (!data_->audio_mutex.try_lock()) {
	#ifdef DEBUG
			printf("\nError trying to lock the audio_mutex: [%s]\n", __FUNCTION__);
	#endif
			return;
		}

		/*int display_list_size = audio_dl_.size();

		for (int i = 0; i < display_list_size; ++i) {
			Command* audio_command = audio_dl_[i].get();
	#ifdef ASSERT
			assert(audio_command && "NULL Audio Command");
	#endif
			audio_command->Execute();
		}*/
	
		//audio_dl_.clear();

		data_->audio_mutex.unlock();

	}
}

// --------------------------------------------------------------//

void Suffer::SufferManager::PrepareAudio() {
	
	/*if (!audio_dl_.empty()) {
		audio_->Awake();
	}*/

}

// --------------------------------------------------------------//

u32 Suffer::SufferManager::GetNumberOfVertexBuffers(){
    return data_->number_of_vertex_buffers_;
}

// --------------------------------------------------------------//

u32 Suffer::SufferManager::GetNumberOfIndexBuffers(){
    return data_->number_of_index_buffers_;
}

// --------------------------------------------------------------//

void Suffer::SufferManager::SumVertexBufferCount(){
    data_->number_of_vertex_buffers_++;
}

// --------------------------------------------------------------//

void Suffer::SufferManager::SumIndexBufferCount(){
    data_->number_of_index_buffers_++;
}

// --------------------------------------------------------------//

bool Suffer::SufferManager::Step(double time_step){

	data_->scene_context_->Step(time_step);
	// This will be the last function in UPDATE
	PrepareAudio();

	return true;
}

// --------------------------------------------------------------//

bool Suffer::SufferManager::Finish(){

	render_manager_.ShutDown();

	return true;
}

// --------------------------------------------------------------//

double Suffer::SufferManager::DeltaTime(){

#ifdef ASSERT
	assert(data_ && "\n Data is null.");
#endif // ASSERT
	return data_->delta_time_;

}

// --------------------------------------------------------------//

Suffer::SufferManager::GPUResource::GPUResource() {

    id_ = -1;
    type_ = kInvalid;

}

// --------------------------------------------------------------//

Suffer::SufferManager::GPUResource::~GPUResource() {

}

// --------------------------------------------------------------//

Suffer::SufferManager::VertexBuffer::VertexBuffer() {

    type_ = GPUResource::kVertexBuffer;
    format_ = kVertexFormat_Invalid;
    id_ = SufferManager::instance().GetNumberOfVertexBuffers();
    SufferManager::instance().SumVertexBufferCount();

}

// --------------------------------------------------------------//

Suffer::SufferManager::IndexBuffer::IndexBuffer() {

    type_ = GPUResource::kIndexBuffer;
    id_ = SufferManager::instance().GetNumberOfIndexBuffers();
    SufferManager::instance().SumIndexBufferCount();

}

// --------------------------------------------------------------//

void Suffer::SufferManager::UploadVertexData(const ref_ptr<VertexBuffer> buffer, Array<float> *data){

#ifdef ASSERT
    assert(buffer.get() != nullptr && "Buffer is NULL!");
#endif

	data_->internal_vertex_buffers_[buffer->id_].data_.copy(*data);
    data_->internal_vertex_buffers_[buffer->id_].version_++;
    data_->internal_vertex_buffers_[buffer->id_].id_handle_ = buffer->id_;

}

// --------------------------------------------------------------//

void Suffer::SufferManager::UploadVertexData(const ref_ptr<VertexBuffer> buffer, float* data, u32 size) {

#ifdef ASSERT
  assert(buffer.get() != nullptr && "Buffer is NULL!");
#endif

  Array<float> vertices_;
  vertices_.alloc(size);
  for (int i = 0; i < size; ++i) {
    vertices_[i] = data[i];
  }

  data_->internal_vertex_buffers_[buffer->id_].data_.copy(vertices_);
  data_->internal_vertex_buffers_[buffer->id_].version_++;
  data_->internal_vertex_buffers_[buffer->id_].id_handle_ = buffer->id_;
}

// --------------------------------------------------------------//

void Suffer::SufferManager::UploadIndexData(const ref_ptr<IndexBuffer> buffer, Array<u16> *data){

#ifdef ASSERT
    assert(buffer.get() != nullptr && "Buffer is NULL!");
#endif
    data_->internal_index_buffers_[buffer->id_].data_.copy(*data);
    data_->internal_index_buffers_[buffer->id_].version_++;
    data_->internal_index_buffers_[buffer->id_].id_handle_ = buffer->id_;

	printf("ID: %d\n", buffer->id_);
	printf("USER VERSION: %d\n", data_->internal_vertex_buffers_[buffer->id_].version_);
}

// --------------------------------------------------------------//

void Suffer::SufferManager::UploadIndexData(const ref_ptr<IndexBuffer> buffer, u16* data, u32 size){

#ifdef ASSERT
  assert(buffer.get() != nullptr && "Buffer is NULL!");
#endif

  Array<u16> indices_;
  indices_.alloc(size);
  for (int i = 0; i < size; ++i) {
    indices_[i] = data[i];
  }

  data_->internal_index_buffers_[buffer->id_].data_.copy(indices_);
  data_->internal_index_buffers_[buffer->id_].version_++;
  data_->internal_index_buffers_[buffer->id_].id_handle_ = buffer->id_;

  printf("ID: %d\n", buffer->id_);
  printf("USER VERSION: %d\n", data_->internal_vertex_buffers_[buffer->id_].version_);
}

// --------------------------------------------------------------//

u32 Suffer::SufferManager::IsBufferCreated(ref_ptr<VertexBuffer> vertex_buffer){
	
#ifdef ASSERT
	assert(vertex_buffer.get() != nullptr);
#endif

	s32 id_vertex = vertex_buffer.get()->id_;
	if (data_->internal_vertex_buffers_[id_vertex].gpu_version_ == 0) {
		glGenBuffers(1, &data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			data_->internal_vertex_buffers_[id_vertex].data_.size(),
			data_->internal_vertex_buffers_[id_vertex].data_.get(),
			GL_STATIC_DRAW);
	}

	if (data_->internal_vertex_buffers_[id_vertex].gpu_version_ < data_->internal_vertex_buffers_[id_vertex].version_) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			data_->internal_vertex_buffers_[id_vertex].data_.size(),
			data_->internal_vertex_buffers_[id_vertex].data_.get(),
			GL_STATIC_DRAW);
	}

	data_->internal_vertex_buffers_[id_vertex].gpu_version_ = data_->internal_vertex_buffers_[id_vertex].version_;
	printf("USER VERSION: %d\n", data_->internal_vertex_buffers_[id_vertex].version_);
	return data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_;
}

// --------------------------------------------------------------//

u32 Suffer::SufferManager::IsMaterialCreated(ref_ptr<Material> material){

#ifdef ASSERT
  assert(material.get() != nullptr);
#endif
  GLenum error;


  if (!data_->internal_materials_[material.get()->GetMaterialType()].is_created_) {
		data_->internal_materials_[material.get()->GetMaterialType()].vertex_shader_id_ = 
      glCreateShader(GL_VERTEX_SHADER);
    error = glGetError();
    data_->internal_materials_[material.get()->GetMaterialType()].fragment_shader_id_ =
      glCreateShader(GL_FRAGMENT_SHADER);
    error = glGetError();

    const GLint vertex_size = strlen(data_->internal_materials_[material.get()->GetMaterialType()].vertex_shader_);
    const GLint fragment_size = strlen(data_->internal_materials_[material.get()->GetMaterialType()].fragment_shader_);

    glShaderSource(data_->internal_materials_[material.get()->GetMaterialType()].vertex_shader_id_,
      1, &data_->internal_materials_[material.get()->GetMaterialType()].vertex_shader_, 
      &vertex_size);
    error = glGetError();
    glShaderSource(data_->internal_materials_[material.get()->GetMaterialType()].fragment_shader_id_,
      1, &data_->internal_materials_[material.get()->GetMaterialType()].fragment_shader_, &fragment_size);
    error = glGetError();

    glCompileShader(data_->internal_materials_[material.get()->GetMaterialType()].vertex_shader_id_);
    error = glGetError();

    GLint status = 0;
    glGetShaderiv(data_->internal_materials_[material.get()->GetMaterialType()].vertex_shader_id_, GL_COMPILE_STATUS, &status);
    GLint log_length = 0;
    glGetShaderiv(data_->internal_materials_[material.get()->GetMaterialType()].vertex_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
    GLchar* info_log = new GLchar[log_length + 1];
    glGetShaderInfoLog(data_->internal_materials_[material.get()->GetMaterialType()].vertex_shader_id_, log_length, &log_length, info_log);
    info_log[log_length] = '\0';
    delete info_log;
    if (status == GL_FALSE)
      printf("\nERROR: vertex shader not compiled");

    glCompileShader(data_->internal_materials_[material.get()->GetMaterialType()].fragment_shader_id_);
    error = glGetError();
    status = 0;
    glGetShaderiv(data_->internal_materials_[material.get()->GetMaterialType()].fragment_shader_id_, GL_COMPILE_STATUS, &status);
    log_length = 0;
    glGetShaderiv(data_->internal_materials_[material.get()->GetMaterialType()].fragment_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
    info_log = new GLchar[log_length + 1];
    glGetShaderInfoLog(data_->internal_materials_[material.get()->GetMaterialType()].fragment_shader_id_, log_length, &log_length, info_log);
    info_log[log_length] = '\0';
    delete info_log;
    if (status == GL_FALSE)
      printf("\nERROR: fragment shader not compiled");

    // PROGRAM
    data_->internal_materials_[material.get()->GetMaterialType()].current_program_ = glCreateProgram();

    error = glGetError();
    glAttachShader(data_->internal_materials_[material.get()->GetMaterialType()].current_program_,
      data_->internal_materials_[material.get()->GetMaterialType()].vertex_shader_id_);

    error = glGetError();
    glAttachShader(data_->internal_materials_[material.get()->GetMaterialType()].current_program_,
      data_->internal_materials_[material.get()->GetMaterialType()].fragment_shader_id_);

    error = glGetError();
    glLinkProgram(data_->internal_materials_[material.get()->GetMaterialType()].current_program_);

    error = glGetError();
    data_->internal_materials_[material.get()->GetMaterialType()].is_created_ = true;
  }

  u32 program_id;

  switch (material.get()->GetMaterialType()) {
  case Suffer::Material::kBasicMaterials_Default:
    program_id = data_->internal_materials_[material.get()->GetMaterialType()].current_program_;
    break;
  case Suffer::Material::kBasicMaterials_Phong:
    break;
  case Suffer::Material::kBasicMaterials_NONE:
    break;
  default:
    break;
  }

  return program_id;
}

// --------------------------------------------------------------//

u32 Suffer::SufferManager::NumberElements(ref_ptr<IndexBuffer> index_buffer){

	printf("IDHandle: %f\nGPUVersion: %f\nSize: %f\nUserVersion:%f",
		data_->internal_index_buffers_[index_buffer->id_].id_handle_,
		data_->internal_index_buffers_[index_buffer->id_].gpu_version_,
		data_->internal_index_buffers_[index_buffer->id_].data_.size(),
		data_->internal_index_buffers_[index_buffer->id_].version_
		);

	return data_->internal_index_buffers_[index_buffer->id_].data_.size();
}

// --------------------------------------------------------------//

u32 Suffer::SufferManager::IsBufferCreated(ref_ptr<IndexBuffer> index_buffer){

#ifdef ASSERT
	assert(index_buffer.get() != nullptr);
#endif

	s32 id_vertex = index_buffer.get()->id_;
	if (data_->internal_index_buffers_[id_vertex].gpu_version_ == 0) {
		glGenBuffers(1, &data_->internal_index_buffers_[id_vertex].current_gl_buffer_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->internal_index_buffers_[id_vertex].current_gl_buffer_);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			data_->internal_index_buffers_[id_vertex].data_.size(),
			data_->internal_index_buffers_[id_vertex].data_.get(),
			GL_STATIC_DRAW);
	}

	if (data_->internal_index_buffers_[id_vertex].gpu_version_ < data_->internal_index_buffers_[id_vertex].version_) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->internal_index_buffers_[id_vertex].current_gl_buffer_);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			data_->internal_index_buffers_[id_vertex].data_.size(),
			data_->internal_index_buffers_[id_vertex].data_.get(),
			GL_STATIC_DRAW);
	}

	data_->internal_index_buffers_[id_vertex].gpu_version_ = data_->internal_index_buffers_[id_vertex].version_;
	return data_->internal_index_buffers_[id_vertex].current_gl_buffer_;

}

// --------------------------------------------------------------//
