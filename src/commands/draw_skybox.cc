/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 03-05-2020
 * Draw Skybox command source
 */

#include "draw_skybox.h"

static const u32 kMaxUsedVec4Data_DrawSkybox = 1;

struct Suffer::DrawSkybox::Data {

  // Geometry
  s32 vertex_buffer_id_;
  s32 index_buffer_id_;

  // Contains the model, view and projections matrixes
  float u_data_[kMaxUsedVec4Data_DrawSkybox * 4];

  u32 cubemap_id_;

};

 // ------------------------------------------------------------------------- //

Suffer::DrawSkybox::DrawSkybox(){

  cmd_type_ = Command::kCommandType_Render;
  data_ = new Data();

}

// ------------------------------------------------------------------------- //

Suffer::DrawSkybox::~DrawSkybox() {

  if (!data_) return;

  delete data_;
  data_ = nullptr;

}

// ------------------------------------------------------------------------- //

void Suffer::DrawSkybox::SetData(Skybox* skybox){

  data_->cubemap_id_ = skybox->cubemap_id_;

}

// ------------------------------------------------------------------------- //

void Suffer::DrawSkybox::Execute() const{



}

// ------------------------------------------------------------------------- //

