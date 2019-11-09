#include <geometry.h>
#include <GL/glew.h>

// --------------------------------------------------- //

struct Geometry::Data {
	GLuint indices_ID;
	GLuint vertices_ID;
	u32 number_elements;
};

// --------------------------------------------------- //

Geometry::Geometry() {
	data_ = new Data();

	data_->vertices_ID = 0;
	data_->indices_ID = 0;

	shape_ = kBasicShapes_NONE;
}

// --------------------------------------------------- //

void Geometry::SetVertexBuffer(ResourceManager::VertexBuffer vertex_buffer){
    vertex_buffer_ = vertex_buffer;
}

// --------------------------------------------------- //

void Geometry::SetIndexBuffer(ResourceManager::IndexBuffer index_buffer){
    index_buffer_ = index_buffer;
}

// --------------------------------------------------- //

s32 Geometry::VertexBuffer(){
    return vertex_buffer_.id_;
}

// --------------------------------------------------- //

s32 Geometry::IndexBuffer(){
    return index_buffer_.id_;
}

// --------------------------------------------------- //

Geometry::~Geometry() {
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

//// --------------------------------------------------- //
//
//void Geometry::SetIndicesID(u16 indices_ID) {
//	data_->indices_ID = indices_ID;
//}
//
//// --------------------------------------------------- //
//
//void Geometry::SetVerticesID(u16 vertices_ID) {
//	data_->vertices_ID = vertices_ID;
//}
//
//// --------------------------------------------------- //
//
//void Geometry::SetNumberElements(u32 number_elements) {
//	data_->number_elements = number_elements;
//}
//
//// --------------------------------------------------- //
//
//u16 Geometry::GetIndicesID() {
//	return data_->indices_ID;
//}
//
//// --------------------------------------------------- //
//
//u16 Geometry::GetVerticesID() {
//	return data_->vertices_ID;
//}
//
//// --------------------------------------------------- //
//
//u32 Geometry::GetNumberElements() {
//	return data_->number_elements;
//}

// --------------------------------------------------- //