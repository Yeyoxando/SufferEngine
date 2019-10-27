#include <material.h>
#include <GL/glew.h>

// --------------------------------------------------- //

struct Material::Data {
	glm::vec4 color;
	GLuint program_ID;
};

// --------------------------------------------------- //

glm::vec4 Material::GetColor() {
	return data_->color;
}

// --------------------------------------------------- //

u16 Material::GetProgramID() {
	return data_->program_ID;
}

// --------------------------------------------------- //

void Material::SetColor(glm::vec4 new_color) {
	data_->color = new_color;
}

// --------------------------------------------------- //

void Material::SetProgram(u16 program) {
	data_->program_ID = program;
}

// --------------------------------------------------- //

Material::Material() {
	data_ = new Data();

	data_->color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

// --------------------------------------------------- //

Material::~Material() {
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------- //