#include "component_geometry.h"
#include <GL/glew.h>
#include "internal_suffermanager.h"
#include "internal_resource_manager.h"
#include "common_definitions.h"

// --------------------------------------------------- //

Suffer::GeometryComponent::GeometryComponent() : Component(Component::kComponentKind_Geometry){

  mode_ = kDrawMode_Triangles;
  shape_ = kBasicShapes_Invalid;

}

// --------------------------------------------------- //

void Suffer::GeometryComponent::SetIndexBuffer(ref_ptr<Suffer::ResourceManager::IndexBuffer> buffer) {
  index_buffer_id_ = buffer.get()->id_;
}

// --------------------------------------------------- //

void Suffer::GeometryComponent::CreateGeometryWithShape(BasicShapes shape) {

  shape_ = shape;
  vertex_buffer_id_ = suffer.resource_manager_.data_->internal_vertex_buffers_[(s32)shape].id_handle_;
  index_buffer_id_ = suffer.resource_manager_.data_->internal_index_buffers_[(s32)shape].id_handle_;

}

// --------------------------------------------------- //

Suffer::GeometryComponent::BasicShapes Suffer::GeometryComponent::GetGeometry(){
    return shape_;
}

// --------------------------------------------------- //

void Suffer::GeometryComponent::SetDrawMode(DrawMode newMode) {
  mode_ = newMode;
}

// --------------------------------------------------- //

Suffer::GeometryComponent::DrawMode Suffer::GeometryComponent::GetDrawMode() {
  return mode_;
}

// --------------------------------------------------- //

void Suffer::GeometryComponent::SetVertexBuffer(ref_ptr<Suffer::ResourceManager::VertexBuffer> buffer) {
  vertex_buffer_id_ = buffer.get()->id_;
}

// --------------------------------------------------- //

void Suffer::GeometryComponent::SetBuffers(ref_ptr<Suffer::ResourceManager::VertexBuffer> vertex_buffer, ref_ptr<Suffer::ResourceManager::IndexBuffer> index_buffer) {
  vertex_buffer_id_ = vertex_buffer.get()->id_;
  index_buffer_id_ = index_buffer.get()->id_;
}

// --------------------------------------------------- //

Suffer::GeometryComponent::~GeometryComponent() {

}

// --------------------------------------------------- //