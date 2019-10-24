#include <suffermanager.h>
#include <imgui.h>
#include <scene.h>
#include <input.h>
#include <window.h>
#include "imgui_impl_opengl3.h"
#include <interface.h>
#include <clear.h>
#include <time.h>
#include <GL/glew.h>

struct SufferManager::Data {

	std::vector<EDK3::ref_ptr<Command>> display_list_;
	EDK3::ref_ptr<Scene> scene_;
	Suffer::Window wind_;
	double previous_time_;
	double current_time_;
	double delta_time_;
	Interface interface_;


};

SufferManager::SufferManager(){
	data_ = new Data();

	data_->display_list_ = std::vector<EDK3::ref_ptr<Command>>(0);
	data_->scene_.alloc();
}

void SufferManager::PrepareDraw(){

	EDK3::ref_ptr<Clear> clear_cmd;

	clear_cmd.alloc();
	clear_cmd.get()->SetClearColor(glm::vec4(0.8f));

	AddCommand(clear_cmd.get());

	data_->scene_->PrepareDraw();

}

SufferManager::~SufferManager(){
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

SufferManager::SufferManager(const SufferManager&){

}

SufferManager& SufferManager::instance() {

	static SufferManager* instance = new SufferManager();
	return *instance;

}

bool SufferManager::Init(){

#ifdef ASSERT
	assert(data_ && "\n Data is null.");
#endif // ASSERT

	data_->wind_.init(800, 600);
	Suffer::InitInput();

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
		gl_FragColor = vec4(0.0f);
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

	glShaderSource( vertex_shader_ID, 1, &vertex_shader, &vertex_size);
	 error = glGetError();
	glShaderSource( fragment_shader_ID, 1, &fragment_shader, &fragment_size);
	 error = glGetError();

	glCompileShader( vertex_shader_ID);
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

	glCompileShader( fragment_shader_ID);
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
	 error = glGetError();
	glAttachShader( program_ID,  vertex_shader_ID);
	 error = glGetError();
	glAttachShader( program_ID,  fragment_shader_ID);
	 error = glGetError();

	glLinkProgram( program_ID);
	 error = glGetError();

		// BUFFERS
	float vertices[] = {
		0.0f,  0.5f, -1.0f,
		0.5f, -0.5f, -1.0f,
		-0.5f, -0.5f, -1.0f
	};

	glGenBuffers(1, & triangle_vertices_ID);
	 error = glGetError();
	glBindBuffer(GL_ARRAY_BUFFER,  triangle_vertices_ID);
	 error = glGetError();
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	error = glGetError();

	unsigned char indices[]{ 0, 2, 1 };

	glGenBuffers(1, &triangle_indices_ID);
	error = glGetError();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_indices_ID);
	error = glGetError();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	error = glGetError();

	data_->scene_->Init();

	return true;
}

bool SufferManager::Run(){

	while (!Suffer::IsKeyDown(k_Escape)) {

		data_->current_time_ = Suffer::RawTime();
		data_->wind_.processEvents();
		//data_->interface_.Update();

		Step(data_->delta_time_);
		
		DrawDisplayList();

		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		data_->wind_.swapBuffers();

		data_->delta_time_ = (data_->current_time_ - data_->previous_time_) * 0.0001f;
		data_->previous_time_ = data_->current_time_;

	
	}

	return true;
}

bool SufferManager::Step(double time_step){

	PrepareDraw();

	return true;
}

bool SufferManager::Finish(){
	return true;
}

double SufferManager::DeltaTime(){
#ifdef ASSERT
	assert(data_ && "\n Data is null.");
#endif // ASSERT
	return data_->delta_time_;
}

bool SufferManager::ResetDisplayList(){
	if (data_->display_list_.empty()) return true;

	data_->display_list_.clear();
	if (data_->display_list_.empty()) return true;
}

void SufferManager::AddCommand(EDK3::ref_ptr<Command> cmd){
	if (!cmd) return;

	data_->display_list_.push_back(cmd);
}

void SufferManager::DrawDisplayList(){
	for (int i = 0; i < data_->display_list_.size(); ++i){
		Command* cmd = data_->display_list_[i].get();
		cmd->Execute();
	}

	ResetDisplayList();
}
