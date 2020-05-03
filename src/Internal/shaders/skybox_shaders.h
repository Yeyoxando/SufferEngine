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
    
    layout(location = 0) in vec3 a_position;
    
// ......... UNIFORMS .........
    uniform vec4 u_data[8];

// ......... DEFINES ..........
    #define u_v_matrix mat4(u_data[0], u_data[1], u_data[2], u_data[3])
    #define u_p_matrix mat4(u_data[4], u_data[5], u_data[6], u_data[7])

// ....... IN / OUT ........
    out vec3 uvs;

// ......... MAIN ..........
    void main(){

      uvs = a_position;
      vec4 position = u_p_matrix * mat4(mat3(u_v_matrix)) * vec4(a_position, 1.0f);
      gl_Position = position.xyww;

    }  

  )VSKYBOX";

  // -- (fragment) --
  static const char* skybox_fragment_shader_ = R"FSKYBOX(
    #version 330

// ......... UNIFORMS .........
    uniform samplerCube u_skybox;

// ....... IN / OUT ........
    in vec3 uvs;
    out vec4 fragColor;

// ......... MAIN ..........
    void main(){
      
      fragColor = texture(u_skybox, uvs);

    }  
  
  )FSKYBOX";

  // --------------------------- SkyboxShaders ----------------------------- //

}

#endif // __SKYBOX_SHADERS_H__