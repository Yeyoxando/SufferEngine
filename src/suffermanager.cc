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
#include "audio_commands.h"

// --------------------------------------------------------------//

struct Suffer::SufferManager::Data {

	Suffer::Window wind_;
	double previous_time_;
	double current_time_;
	double delta_time_;
	Interface interface_;

	ref_ptr<Scene> scene_context_;

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

	data_->wind_.init(WINDOW_WIDTH, WINDOW_HEIGHT);
	Suffer::InitInput();
	data_->interface_.Init();

	//Subsystems init
  audio_manager_.StartUp();
  render_manager_.StartUp();

	// Threads Allocation
	logic_.alloc();
	input_.alloc();
	audio_.alloc();


	data_->InitInternalBuffers();
	data_->InitInternalMaterials();

	data_->window_should_close_ = false;

	data_->scene_context_->Init();

	// Threads Function Assignment
	auto audio_thread = [] { SufferManager::instance().Audio(); };
	audio_.get()->NewTask(audio_thread);

	auto update_thread = [] { SufferManager::instance().Update(); };
	logic_.get()->NewTask(update_thread);

	auto input_thread = [] { SufferManager::instance().Input(); };
	input_.get()->NewTask(input_thread);

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

  //ref_ptr<Audio3D> audio_source_;
  //audio_source_.alloc();
  //audio_source_->Load("../../../resources/audio/plonk_dry.ogg");
  //ref_ptr <AudioCommands::Play> play_command_;
  //play_command_.alloc();
  //play_command_->audio_3d_ = audio_source_.get();
  //DisplayList audio_dl_;
  //audio_dl_.addCommand(play_command_.get());
  //audio_manager_.AddToAudioQueue(std::move(audio_dl_));

	while (!data_->window_should_close_) {

    SetMousePosition();

		data_->current_time_ = Suffer::RawTime();
		data_->wind_.processEvents();
		
		input_->Awake();
		
    logic_->Awake();

		Draw();
    
    //logic_->WaitMe();

		data_->delta_time_ = (data_->current_time_ - data_->previous_time_) * 0.0001f;
		data_->previous_time_ = data_->current_time_;

	}

	return true;

}

// --------------------------------------------------------------//

void Suffer::SufferManager::Audio() {

	while (1) {

		audio_->Sleep();
    audio_manager_.DoAudio();

	}
}

// --------------------------------------------------------------//

void Suffer::SufferManager::PrepareAudio() {
	
    if (audio_manager_.audio_dl_.size() > 0) {
        audio_->Awake();
    }

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
  audio_manager_.ShutDown();

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
    assert(buffer.get()->format_ != VertexBuffer::kVertexFormat_Invalid && "Vertex format is INVALID!");
#endif

	data_->internal_vertex_buffers_[buffer->id_].data_.copy(*data);
    data_->internal_vertex_buffers_[buffer->id_].version_++;
    data_->internal_vertex_buffers_[buffer->id_].id_handle_ = buffer->id_;

}

// --------------------------------------------------------------//

void Suffer::SufferManager::UploadVertexData(const ref_ptr<VertexBuffer> buffer, float* data, u32 size) {

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

void Suffer::SufferManager::UploadIndexData(const ref_ptr<IndexBuffer> buffer, Array<u16> *data){

#ifdef ASSERT
  assert(buffer.get() != nullptr && "Buffer is NULL!");
#endif
    data_->internal_index_buffers_[buffer->id_].data_.copy(*data);
    data_->internal_index_buffers_[buffer->id_].version_++;
    data_->internal_index_buffers_[buffer->id_].id_handle_ = buffer->id_;

}

// --------------------------------------------------------------//

void Suffer::SufferManager::UploadIndexData(const ref_ptr<IndexBuffer> buffer, u16* data, u32 size){

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

u32 Suffer::SufferManager::IsBufferCreated(const VertexBuffer* vertex_buffer){
	
#ifdef ASSERT
	assert(vertex_buffer != nullptr);
#endif
  if (vertex_buffer->id_ < 0) return 0;
	s32 id_vertex = vertex_buffer->id_;
	if (data_->internal_vertex_buffers_[id_vertex].gpu_version_ == 0) {
		glGenBuffers(1, &data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);
		glBindBuffer(GL_ARRAY_BUFFER, data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);

		glBufferData(GL_ARRAY_BUFFER,
			data_->internal_vertex_buffers_[id_vertex].data_.sizeInBytes(),
			data_->internal_vertex_buffers_[id_vertex].data_.get(),
      GL_STATIC_DRAW);
    data_->internal_vertex_buffers_[id_vertex].gpu_version_ = data_->internal_vertex_buffers_[id_vertex].version_;
	}

	if (data_->internal_vertex_buffers_[id_vertex].gpu_version_ < data_->internal_vertex_buffers_[id_vertex].version_) {
		glBindBuffer(GL_ARRAY_BUFFER, data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);

		glBufferData(GL_ARRAY_BUFFER,
			data_->internal_vertex_buffers_[id_vertex].data_.sizeInBytes(),
			data_->internal_vertex_buffers_[id_vertex].data_.get(),
      GL_STATIC_DRAW);
    data_->internal_vertex_buffers_[id_vertex].gpu_version_ = data_->internal_vertex_buffers_[id_vertex].version_;
	}

	return data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_;
}

// --------------------------------------------------------------//

u32 Suffer::SufferManager::IsBufferCreated(const IndexBuffer* index_buffer) {

#ifdef ASSERT
  assert(index_buffer != nullptr);
#endif
  if (index_buffer->id_ < 0) return 0;
  GLenum error = glGetError();
  s32 id_index = index_buffer->id_;
  if (data_->internal_index_buffers_[id_index].gpu_version_ == 0) {
    glGenBuffers(1, &data_->internal_index_buffers_[id_index].current_gl_buffer_);
    error = glGetError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->internal_index_buffers_[id_index].current_gl_buffer_);
    error = glGetError();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
      data_->internal_index_buffers_[id_index].data_.sizeInBytes(),
      data_->internal_index_buffers_[id_index].data_.get(),
      GL_STATIC_DRAW);
    error = glGetError();
  }

  if (data_->internal_index_buffers_[id_index].gpu_version_ < data_->internal_index_buffers_[id_index].version_) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->internal_index_buffers_[id_index].current_gl_buffer_);
    error = glGetError();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
      data_->internal_index_buffers_[id_index].data_.sizeInBytes(),
      data_->internal_index_buffers_[id_index].data_.get(),
      GL_STATIC_DRAW);
    error = glGetError();
  }

  data_->internal_index_buffers_[id_index].gpu_version_ = data_->internal_index_buffers_[id_index].version_;
  return data_->internal_index_buffers_[id_index].current_gl_buffer_;

}

// --------------------------------------------------------------//

u32 Suffer::SufferManager::IsMaterialCreated(const Material* material){

#ifdef ASSERT
  assert(material != nullptr);
#endif
  GLenum error;

  u32 mat_type = material->GetMaterialParamsType();
  if (mat_type > 1000) return 0;
  if (!data_->internal_materials_[mat_type].is_created_) {
		data_->internal_materials_[mat_type].vertex_shader_id_ =
      glCreateShader(GL_VERTEX_SHADER);
    error = glGetError();
    data_->internal_materials_[mat_type].fragment_shader_id_ =
      glCreateShader(GL_FRAGMENT_SHADER);
    error = glGetError();

    const GLint vertex_size = strlen(data_->internal_materials_[mat_type].vertex_shader_);
    const GLint fragment_size = strlen(data_->internal_materials_[mat_type].fragment_shader_);

    glShaderSource(data_->internal_materials_[mat_type].vertex_shader_id_,
      1, &data_->internal_materials_[mat_type].vertex_shader_,
      &vertex_size);
    error = glGetError();
    glShaderSource(data_->internal_materials_[mat_type].fragment_shader_id_,
      1, &data_->internal_materials_[mat_type].fragment_shader_, &fragment_size);
    error = glGetError();

    glCompileShader(data_->internal_materials_[mat_type].vertex_shader_id_);
    error = glGetError();

    GLint status = 0;
    glGetShaderiv(data_->internal_materials_[mat_type].vertex_shader_id_, GL_COMPILE_STATUS, &status);
    GLint log_length = 0;
    glGetShaderiv(data_->internal_materials_[mat_type].vertex_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
    GLchar* info_log = new GLchar[log_length + 1];
    glGetShaderInfoLog(data_->internal_materials_[mat_type].vertex_shader_id_, log_length, &log_length, info_log);
    info_log[log_length] = '\0';
    printf("%s", info_log);
    delete info_log;
    if (status == GL_FALSE)
      printf("\nERROR: vertex shader not compiled");

    glCompileShader(data_->internal_materials_[mat_type].fragment_shader_id_);
    error = glGetError();
    status = 0;
    glGetShaderiv(data_->internal_materials_[mat_type].fragment_shader_id_, GL_COMPILE_STATUS, &status);
    log_length = 0;
    glGetShaderiv(data_->internal_materials_[mat_type].fragment_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
    info_log = new GLchar[log_length + 1];
    glGetShaderInfoLog(data_->internal_materials_[mat_type].fragment_shader_id_, log_length, &log_length, info_log);
    info_log[log_length] = '\0';
    printf("%s", info_log);
    delete info_log;
    if (status == GL_FALSE)
      printf("\nERROR: fragment shader not compiled");

    // PROGRAM
    data_->internal_materials_[mat_type].current_program_ = glCreateProgram();

    error = glGetError();
    glAttachShader(data_->internal_materials_[mat_type].current_program_,
      data_->internal_materials_[mat_type].vertex_shader_id_);

    error = glGetError();
    glAttachShader(data_->internal_materials_[mat_type].current_program_,
      data_->internal_materials_[mat_type].fragment_shader_id_);

    error = glGetError();
    glLinkProgram(data_->internal_materials_[mat_type].current_program_);

    error = glGetError();
    data_->internal_materials_[mat_type].is_created_ = true;
  }

  u32 program_id;

  // We used to have a switch here with material type, but its not needed
  program_id = data_->internal_materials_[mat_type].current_program_;

  return program_id;
}

// --------------------------------------------------------------//

u32 Suffer::SufferManager::NumberElements(const IndexBuffer* index_buffer){
  if (index_buffer->id_ < 0) return 0;
	return data_->internal_index_buffers_[index_buffer->id_].data_.size();
}

// --------------------------------------------------------------//

mathmorra::Vector2 Suffer::SufferManager::GetMousePosition(){
    return mouse_position_;
}

// --------------------------------------------------------------//

void Suffer::SufferManager::SetMousePosition(){

    mouse_position_.x_ = Suffer::MousePositionX();
    mouse_position_.y_ = Suffer::MousePositionY();

}

// --------------------------------------------------------------//

