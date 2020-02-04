// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __INTERNAL_RENDER_MANAGER_H__
#define __INTERNAL_RENDER_MANAGER_H__

#include "render_manager.h"
#include "game_object.h"
#include "component_material.h"

// ------------------------------------------------------------------------- //

struct Suffer::RenderManager::RenderData {
 
  RenderData();
  ~RenderData();

  ref_ptr<GameObject> screen_quad_;
  Suffer::Material::RenderToTextureParams* reference_to_texture_params_; // Render to texture

};

// ------------------------------------------------------------------------- //

#endif 