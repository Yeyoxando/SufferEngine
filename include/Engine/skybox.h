// Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "referenced.h"
#include "ref_ptr.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  class Skybox : public Referenced {
  public:
    Skybox();
    ~Skybox();

    void SetTextures(const char* src_right,
                     const char* src_left,
                     const char* src_top,
                     const char* src_bottom,
                     const char* src_front,
                     const char* src_back);

  private:
    u32 cubemap_id_;

  };

  // ----------------------------------------------------------------------- //

};

#endif //__SKYBOX_H__