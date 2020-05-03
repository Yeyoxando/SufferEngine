// Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "referenced.h"
#include "resource_manager.h"
#include "ref_ptr.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  class Skybox : public Referenced {
  public:
    Skybox();
    ~Skybox();

    void SetCubemap(ref_ptr<ResourceManager::Cubemap> cubemap);

  private:
    u32 cubemap_id_;

  };

  // ----------------------------------------------------------------------- //

};

#endif //__SKYBOX_H__