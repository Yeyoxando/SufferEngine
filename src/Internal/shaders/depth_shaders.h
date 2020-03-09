// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __DEPTH_SHADERS_H__
#define __DEPTH_SHADERS_H__

namespace Suffer {

  // ------------------------- ShadowDepthShaders -------------------------- //
  // -- (vertex) --
  static const char* shadow_depth_vertex_shader_ = R"VSHADOWDEPTH(
    #version 330
    layout(location = 0) in vec3 a_position;
    
// ......... UNIFORMS .........
    uniform vec4 u_data[12];

// ......... DEFINES ..........
    #define model0 u_data[0]
    #define model1 u_data[1]
    #define model2 u_data[2]
    #define model3 u_data[3]

    #define light_view0 u_data[4]
    #define light_view1 u_data[5]
    #define light_view2 u_data[6]
    #define light_view3 u_data[7]

    #define light_projection0 u_data[8]
    #define light_projection1 u_data[9]
    #define light_projection2 u_data[10]
    #define light_projection3 u_data[11]

// ......... MAIN ..........
    void main(){
      mat4 u_m_matrix = mat4(model0, model1, model2, model3);
      mat4 u_v_matrix = mat4(light_view0, light_view1, light_view2, light_view3);
      mat4 u_p_matrix = mat4(light_projection0, light_projection1, light_projection2, light_projection3); 

      mat4 accum_matrix = u_p_matrix * u_v_matrix * u_m_matrix;

	    gl_Position = accum_matrix * vec4(a_position, 1.0f);
    }  
  
  )VSHADOWDEPTH";


  // -- (fragment) --
  static const char* shadow_depth_fragment_shader_ = R"FSHADOWDEPTH(
    #version 330

// ......... MAIN ..........
    void main(){
      //Do nothing because normally draws depth buffer itself
      //gl_FragDepth = gl_FragCoord.z;
    }
  
  )FSHADOWDEPTH";

  // ------------------------- ShadowDepthShaders -------------------------- //

}

#endif