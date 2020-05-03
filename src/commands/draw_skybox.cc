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


};

 // ------------------------------------------------------------------------- //

Suffer::DrawSkybox::DrawSkybox(){



}

// ------------------------------------------------------------------------- //

void Suffer::DrawSkybox::SetData(Skybox* skybox){



}

// ------------------------------------------------------------------------- //

Suffer::DrawSkybox::~DrawSkybox(){



}

// ------------------------------------------------------------------------- //

void Suffer::DrawSkybox::Execute() const{



}

// ------------------------------------------------------------------------- //

