#include "component_geometry.h"
#include <GL/glew.h>
#include "internal_suffermanager.h"
#include "internal_resource_manager.h"
#include "common_definitions.h"

#define TINYOBJLOADER_IMPLEMENTATION 
#include "tiny_obj_loader.h"

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

void Suffer::GeometryComponent::LoadFromOBJ(const char* obj_path, const char* material_path){

    if (nullptr == obj_path) {
        printf("ERROR: NULL File path in: [%s].\n", __FUNCTION__);
        assert(nullptr != obj_path && "ERROR: NULL File path.");
        return;
    }

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t>shapes;
    std::vector<tinyobj::material_t>materials;
    std::string error;

    bool ret = LoadObj(&attrib, &shapes, &materials, &error, nullptr, obj_path, material_path);


    u32 number_vertices_ = 0;
    u32 number_normals_ = 0;
    u32 number_indices_ = 0;

    number_vertices_ += attrib.vertices.size();
    number_normals_ += attrib.normals.size();
    number_indices_ += attrib.texcoords.size();

    Array<Suffer::ResourceManager::VertexBuffer::Vertex> vertex_buffers_;

    u64 total_vertices = (attrib.vertices.size()) + (attrib.normals.size()) + (attrib.texcoords.size());
    vertex_buffers_.alloc(total_vertices);

    // Loop over shapes
    u32 index_ = 0;
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex

                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                // VERTICES
                tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
                tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
                tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];

                vertex_buffers_[index_].vertices_.x_ = vx;
                vertex_buffers_[index_].vertices_.y_ = vy;
                vertex_buffers_[index_].vertices_.z_ = vz;


                // NORMALS
                tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
                tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
                tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];

                vertex_buffers_[index_].normals_.x_ = nx;
                vertex_buffers_[index_].normals_.y_ = ny;
                vertex_buffers_[index_].normals_.z_ = nz;


                // TEXTURE COORDS
                tinyobj::real_t tx = attrib.texcoords[idx.texcoord_index + 0];
                tinyobj::real_t ty = attrib.texcoords[idx.texcoord_index + 1];

                vertex_buffers_[index_].uvs_.x_ = tx;
                vertex_buffers_[index_].uvs_.y_ = ty;

                ++index_;

            }
            index_offset += fv;

            // per-face material
            shapes[s].mesh.material_ids[f];
        }
    }

    //vertex_buffer_.UploadVertexData()

    printf("TINY ERROR: %s.\n", error.c_str());

}

// --------------------------------------------------- //

Suffer::GeometryComponent::~GeometryComponent() {

}

// --------------------------------------------------- //