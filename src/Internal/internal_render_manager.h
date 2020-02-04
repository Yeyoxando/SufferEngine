// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __INTERNAL_RENDER_MANAGER_H__
#define __INTERNAL_RENDER_MANAGER_H__

#include "render_manager.h"
#include "game_object.h"

// ------------------------------------------------------------------------- //

struct Suffer::RenderManager::RenderData {
 
  RenderData();
  ~RenderData();

  ref_ptr<GameObject> screen_quad_;

};

// ------------------------------------------------------------------------- //

#endif 