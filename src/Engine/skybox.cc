// Diego Ochando Torres <ochandoto@esat-alumni.com>

#include "skybox.h"

// ----------------------------------------------------------------------- //

Suffer::Skybox::Skybox(){


}

// ----------------------------------------------------------------------- //

Suffer::Skybox::~Skybox(){


}

// ----------------------------------------------------------------------- //

void Suffer::Skybox::SetCubemap(ref_ptr<ResourceManager::Cubemap> cubemap) {

  //Will create a internal cubemap and store their reference id
  // Later will use to create a draw skybox command
  // It will be added at the end of render system dl on suffermanager

  // Load textures one by one and store data in cubemap

  // Initialize and do GL things on the skybox command


  //USE
  // Scene will have a SetSkybox function, 
  // so you only need to create one and set it to the scene.

}

// ----------------------------------------------------------------------- //

