// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __INTERNAL_RENDER_MANAGER_H__
#define __INTERNAL_RENDER_MANAGER_H__

#include "render_manager.h"
#include "postprocessing.h"
#include "game_object.h"
#include "component_material.h"

// ------------------------------------------------------------------------- //

struct Suffer::RenderManager::RenderData {
 
  RenderData();
  ~RenderData();

  ref_ptr<GameObject> screen_quad_;
  ref_ptr<DrawGeometry> draw_quad_command_;
  ref_ptr<Postprocessing> post_command_;
  MaterialComponent::RenderToTextureParams* reference_to_texture_params_; // Render to texture

};

// ------------------------------------------------------------------------- //

#endif 