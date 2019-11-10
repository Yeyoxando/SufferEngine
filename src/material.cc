#include <material.h>
#include <GL/glew.h>

// --------------------------------------------------- //

struct Suffer::Material::Data {
	glm::vec4 color;
	GLuint program_ID;
};

// --------------------------------------------------- //

glm::vec4 Suffer::Material::GetColor() {
	return data_->color;
}

// --------------------------------------------------- //

u16 Suffer::Material::GetProgramID() {
	return data_->program_ID;
}

// --------------------------------------------------- //

void Suffer::Material::SetColor(glm::vec4 new_color) {
	data_->color = new_color;
}

// --------------------------------------------------- //

void Suffer::Material::SetProgram(u16 program) {
	data_->program_ID = program;
}

// --------------------------------------------------- //

Suffer::Material::Material() {
	data_ = new Data();

	data_->color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

// --------------------------------------------------- //

Suffer::Material::~Material() {
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------- //