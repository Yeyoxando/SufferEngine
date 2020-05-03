/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 03-05-2020
 * Skybox shaders header
 */

#ifndef __SKYBOX_SHADERS_H__
#define __SKYBOX_SHADERS_H__

namespace Suffer {

  // --------------------------- SkyboxShaders ----------------------------- //
  // -- (vertex) --
  static const char* skybox_vertex_shader_ = R"VSKYBOX(
    #version 330
    
// ......... MAIN ..........
    void main(){

    }  

  )VSKYBOX";


  // -- (fragment) --
  static const char* skybox_fragment_shader_ = R"FSKYBOX(
    #version 330

// ......... MAIN ..........
    void main(){

    }  
  
  )FSKYBOX";

  // --------------------------- SkyboxShaders ----------------------------- //

}

#endif // __SKYBOX_SHADERS_H__