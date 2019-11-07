#include <suffermanager.h>
#include <imgui.h>
#include <input.h>
#include <window.h>
#include "imgui_impl_opengl3.h"
#include <interface.h>
#include <clear.h>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// --------------------------------------------------------------//

struct SufferManager::Data {

	//std::vector<ref_ptr<Command>> display_list_;
	ref_ptr<Scene> scene_;
	Suffer::Window wind_;
	double previous_time_;
	double current_time_;
	double delta_time_;
	Interface interface_;

	// Mutexes
  Mutex audio_mutex;
  Mutex render_mutex;
	


	// Running
	bool window_should_close_;

	// Predefined geometries
	struct InternalGeometry {
		GLuint vertices_ID;
		GLuint indices_ID;
		u32 number_elements;
	
		void CreateGeometry(Geometry::BasicShapes shape);
	};

	InternalGeometry triangle_; 
	InternalGeometry quad_; 
	InternalGeometry cube_; 

	void InitInternalGeometries();
								  
	// Predefined materials
	struct InternalMaterial {
		GLuint program_ID;
		GLuint vertex_shader_ID;
		GLuint fragment_shader_ID;

		void CreateMaterial(Material::BasicMaterials material);
	};

	InternalMaterial default_material_;

	void InitInternalMaterials();

};

// --------------------------------------------------------------//

void SufferManager::Data::InitInternalGeometries() {
	triangle_.CreateGeometry(Geometry::kBasicShapes_Triangle);
	quad_.CreateGeometry(Geometry::kBasicShapes_Quad);
	cube_.CreateGeometry(Geometry::kBasicShapes_Cube);
}

// --------------------------------------------------------------//

void SufferManager::Data::InitInternalMaterials(){
	default_material_.CreateMaterial(Material::kBasicMaterials_Default);
}

// --------------------------------------------------------------//

void SufferManager::Data::InternalGeometry::CreateGeometry(Geometry::BasicShapes shape){
	switch (shape) {
	case Geometry::kBasicShapes_Triangle: {
		// BUFFERS
		float vertices[] = {
			0.0f,  0.5f, -1.0f,
			0.5f, -0.5f, -1.0f,
			-0.5f, -0.5f, -1.0f
		};

		glGenBuffers(1, &vertices_ID);
		glBindBuffer(GL_ARRAY_BUFFER, vertices_ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		unsigned char indices[]{ 0, 2, 1 };

		glGenBuffers(1, &indices_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		number_elements = 3;

		break;
	}
	case Geometry::kBasicShapes_Quad: {

		// BUFFERS
		float vertices[] = {
			0.5f, -0.5f, -1.0f,
			0.5f,  0.5f, -1.0f,
		   -0.5f,  0.5f, -1.0f,
		   -0.5f, -0.5f, -1.0f,
		};

		glGenBuffers(1, &vertices_ID);
		glBindBuffer(GL_ARRAY_BUFFER, vertices_ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		unsigned char indices[]{ 0, 2, 1, 
								 2, 3, 0 };

		glGenBuffers(1, &indices_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		number_elements = 6;

		break;

	}
	case Geometry::kBasicShapes_Cube: {

		// BUFFERS
		float vertices[] = {
			// front
			-0.5, -0.5,  0.5,
			 0.5, -0.5,  0.5,
			 0.5,  0.5,  0.5,
			-0.5,  0.5,  0.5,
			// back
			-0.5, -0.5, -0.5,
			 0.5, -0.5, -0.5,
			 0.5,  0.5, -0.5,
			-0.5,  0.5, -0.5
		};

		glGenBuffers(1, &vertices_ID);
		glBindBuffer(GL_ARRAY_BUFFER, vertices_ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		unsigned char indices[]{ 		
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3 
		};

		glGenBuffers(1, &indices_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		number_elements = 36;

		break;
	}
	case Geometry::kBasicShapes_NONE:
		break;
	default:
		break;
	}

}

// --------------------------------------------------------------//

void SufferManager::Data::InternalMaterial::CreateMaterial(Material::BasicMaterials material) {
	switch (material) {
	case Material::kBasicMaterials_Default: {
		// DEFAULT SHADERS
		const GLchar* vertex_shader = R"VSHADER(
	
	#version 330
	layout(location = 0) in vec3 a_position;

	void main(){
		gl_Position = vec4(a_position, 1.0f);
	}

	)VSHADER";

		const GLchar* fragment_shader = R"FSHADER(

	#version 330

	void main(){
		gl_FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	}
	
	)FSHADER";

		// HELLO TRIANGLE STUFF -> TODO: THIS WILL BE DELETED
		GLenum error = glGetError();
		vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
		error = glGetError();
		fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
		error = glGetError();

		const GLint vertex_size = strlen(vertex_shader);
		const GLint fragment_size = strlen(fragment_shader);

		glShaderSource(vertex_shader_ID, 1, &vertex_shader, &vertex_size);
		error = glGetError();
		glShaderSource(fragment_shader_ID, 1, &fragment_shader, &fragment_size);
		error = glGetError();

		glCompileShader(vertex_shader_ID);
		error = glGetError();

		GLint status = 0;
		glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &status);
		GLint log_length = 0;
		glGetShaderiv(vertex_shader_ID, GL_INFO_LOG_LENGTH, &log_length);
		GLchar* info_log = new GLchar[log_length + 1];
		glGetShaderInfoLog(vertex_shader_ID, log_length, &log_length, info_log);
		info_log[log_length] = '\0';
		delete info_log;
		if (status == GL_FALSE)
			printf("\nERROR: vertex shader not compiled");

		glCompileShader(fragment_shader_ID);
		error = glGetError();
		status = 0;
		glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &status);
		log_length = 0;
		glGetShaderiv(fragment_shader_ID, GL_INFO_LOG_LENGTH, &log_length);
		info_log = new GLchar[log_length + 1];
		glGetShaderInfoLog(fragment_shader_ID, log_length, &log_length, info_log);
		info_log[log_length] = '\0';
		delete info_log;
		if (status == GL_FALSE)
			printf("\nERROR: fragment shader not compiled");

		// PROGRAM
		program_ID = glCreateProgram();

		glAttachShader(program_ID, vertex_shader_ID);
		glAttachShader(program_ID, fragment_shader_ID);

		glLinkProgram(program_ID);
		
		break;
	}
	case Material::kBasicMaterials_NONE: {
		break;
	}
	default:
		break;
	}

}

// --------------------------------------------------------------//

SufferManager::SufferManager(){

	data_ = new Data();

	//data_->display_list_ = std::vector<ref_ptr<Command>>(0);
	audio_dl_ = std::vector<ref_ptr<Command>>(0);
	data_->scene_.alloc();

}

// --------------------------------------------------------------//

SufferManager::~SufferManager(){
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------------------//

SufferManager::SufferManager(const SufferManager&){

}

// --------------------------------------------------------------//

SufferManager& SufferManager::instance() {

	static SufferManager* instance = new SufferManager();
	return *instance;

}

// --------------------------------------------------------------//

bool SufferManager::Init(){

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


	data_->InitInternalMaterials();
	data_->InitInternalGeometries();

	data_->window_should_close_ = false;


	data_->scene_->Init();
	//newSong.alloc();

	return true;
}

// --------------------------------------------------------------//

void SufferManager::Update() {

	while(1){
		Step(data_->delta_time_);
		logic_->Sleep();
	}

}

// --------------------------------------------------------------//

void SufferManager::Draw() {

	data_->interface_.Update();
	data_->interface_.Render();

	render_manager_.DoRender();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	data_->wind_.swapBuffers();

}

// --------------------------------------------------------------//

void SufferManager::Input() {

	while (1) {
		input_->Sleep();

		// Window Should Close
		if (Suffer::IsKeyDown(k_Escape)) {
			data_->window_should_close_ = true;
		}
	}

}

// --------------------------------------------------------------//

bool SufferManager::Run(){

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

void SufferManager::Audio() {

	while (1) {

		audio_->Sleep();

		if (!data_->audio_mutex.try_lock()) {
	#ifdef DEBUG
			printf("\nError trying to lock the audio_mutex: [%s]\n", __FUNCTION__);
	#endif
			return;
		}

		int display_list_size = audio_dl_.size();

		for (int i = 0; i < display_list_size; ++i) {
			Command* audio_command = audio_dl_[i].get();
	#ifdef ASSERT
			assert(audio_command && "NULL Audio Command");
	#endif
			audio_command->Execute();
		}
	
		audio_dl_.clear();

		data_->audio_mutex.unlock();

	}
}

// --------------------------------------------------------------//

void SufferManager::PrepareAudio() {
	
	if (!audio_dl_.empty()) {
		audio_->Awake();
	}

}

// --------------------------------------------------------------//

bool SufferManager::Step(double time_step){

	//PrepareDraw();
	data_->scene_->Step(time_step);
	// This will be the last function in UPDATE
	PrepareAudio();

	return true;
}

// --------------------------------------------------------------//

bool SufferManager::Finish(){
	render_manager_.ShutDown();

	return true;
}

// --------------------------------------------------------------//

double SufferManager::DeltaTime(){

#ifdef ASSERT
	assert(data_ && "\n Data is null.");
#endif // ASSERT
	return data_->delta_time_;

}

// --------------------------------------------------------------//

//bool SufferManager::ResetDisplayList(){
//	if (data_->display_list_.empty()) return true;
//
//	data_->display_list_.clear();
//	if (data_->display_list_.empty()) return true;
//}
//
//// --------------------------------------------------------------//
//
//void SufferManager::AddCommand(ref_ptr<Command> cmd){
//	if (!cmd) return;
//
//	data_->display_list_.push_back(cmd);
//}
//
//void SufferManager::AddCommand(std::vector<ref_ptr<Command>> *displayList, ref_ptr<Command> cmd){
//	
//	if (!cmd) return;
//	displayList->push_back(cmd);
//
//}

// --------------------------------------------------------------//

void SufferManager::SetPredefiniedShape(ref_ptr <Geometry> geo, Geometry::BasicShapes shape) {
#ifdef ASSERT
	assert(geo.get()); // "geo was NULL"
#endif
	Data::InternalGeometry predefinied_shape;
	
	switch (shape) {
	case Geometry::BasicShapes::kBasicShapes_Triangle: 
		predefinied_shape = data_->triangle_;
		break;
	case Geometry::BasicShapes::kBasicShapes_Quad:
		predefinied_shape = data_->quad_;
		break;
	case Geometry::BasicShapes::kBasicShapes_Cube:
		predefinied_shape = data_->cube_;
		break;
	case Geometry::BasicShapes::kBasicShapes_NONE: 
		break;
	default:
		break;
	}

	geo.get()->shape_ = shape;
	geo.get()->SetIndicesID(predefinied_shape.indices_ID);
	geo.get()->SetVerticesID(predefinied_shape.vertices_ID);
	geo.get()->SetNumberElements(predefinied_shape.number_elements);
}

// --------------------------------------------------------------//

void SufferManager::SetPredefiniedMaterial(ref_ptr <Material> mat, Material::BasicMaterials basic_mat){

#ifdef ASSERT
	assert(mat.get()); // "mat was NULL"
#endif
	
	Data::InternalMaterial predefinied_material;
	
	switch (basic_mat) {
	case Material::BasicMaterials::kBasicMaterials_Default: {
		predefinied_material = data_->default_material_;
		break;
	}
	case Material::BasicMaterials::kBasicMaterials_NONE: {
		break;
	}
	default:
		break;
	}

	mat.get()->material_ = basic_mat;
	mat.get()->SetProgram(predefinied_material.program_ID);
}

// --------------------------------------------------------------//

//void SufferManager::DrawDisplayList(){
//
//	if (!data_->render_mutex.try_lock()) {
//#ifdef DEBUG
//		printf("\nError trying to lock the render_mutex: [%s]\n", __FUNCTION__);
//#endif
//		return;
//	}
//
//	for (int i = 0; i < data_->display_list_.size(); ++i) {
//		Command* cmd = data_->display_list_[i].get();
//		cmd->Execute();
//	}
//
//	ResetDisplayList();
//
//	data_->render_mutex.unlock();
//}
//
//// --------------------------------------------------------------//