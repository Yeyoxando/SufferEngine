#include <geometry.h>
#include <GL/glew.h>

// --------------------------------------------------- //

struct Suffer::Geometry::Data {


};

// --------------------------------------------------- //

Suffer::Geometry::Geometry() {

	data_ = new Data();
  mode_ = kDrawMode_Triangles;
	shape_ = kBasicShapes_NONE;

}

// --------------------------------------------------- //

void Suffer::Geometry::SetIndexBuffer(ref_ptr<Suffer::ResourceManager::IndexBuffer> buffer){
	index_buffer_ = buffer.get();
}

// --------------------------------------------------- //

void Suffer::Geometry::SetDrawMode(DrawMode newMode){
    mode_ = newMode;
}

// --------------------------------------------------- //

Suffer::Geometry::DrawMode Suffer::Geometry::GetDrawMode(){
    return mode_;
}

// --------------------------------------------------- //

void Suffer::Geometry::SetVertexBuffer(ref_ptr<Suffer::ResourceManager::VertexBuffer> buffer){
	vertex_buffer_ = buffer.get();
}

// --------------------------------------------------- //

void Suffer::Geometry::SetBuffers(ref_ptr<Suffer::ResourceManager::VertexBuffer> vertex_buffer, ref_ptr<Suffer::ResourceManager::IndexBuffer> index_buffer) {
	vertex_buffer_ = vertex_buffer.get();
	index_buffer_ = index_buffer.get();
}

// --------------------------------------------------- //

Suffer::Geometry::~Geometry() {
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------- //

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