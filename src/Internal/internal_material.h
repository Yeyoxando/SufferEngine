// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __INTERNAL_MATERIAL_H__
#define __INTERNAL_MATERIAL_H__

#include "material.h"
#include <GL/glew.h>


// --------------------------------------------------- //

struct Suffer::MaterialInstance::Data {

  GLuint program_ID;

  BaseParams* current_params_;

};

// --------------------------------------------------- //

#endif // __INTERNAL_MATERIAL_H__