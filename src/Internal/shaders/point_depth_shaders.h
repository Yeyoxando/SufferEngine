// Author: Palbo

#ifndef __POINT_SHADOW_DEPTH_SHADERS_H__
#define __POINT_SHADOW_DEPTH_SHADERS_H__

namespace Suffer {

  // ------------------------- PointShadowDepthShaders -------------------------- //
  // -- (vertex) --
  static const char* point_shadow_depth_vertex_shader_ = R"VPOINTDEPTH(
    #version 330
    layout(location = 0) in vec3 a_position;
    
// ......... UNIFORMS .........
    uniform vec4 u_data[29];

// ......... DEFINES ..........
    #define model0 u_data[0]
    #define model1 u_data[1]
    #define model2 u_data[2]
    #define model3 u_data[3]

// ......... MAIN ..........
    void main(){
      mat4 u_m_matrix = mat4(model0, model1, model2, model3);
	    gl_Position = u_m_matrix * vec4(a_position, 1.0f);
    }  
  
  )VPOINTDEPTH";



  // -- (geometry) --
  static const char* point_shadow_depth_geometry_shader_ = R"GPOINTDEPTH(
        #version 330
        layout (triangles) in;
        layout (triangle_strip, max_vertices=18) out;

    // ......... UNIFORMS .........
        uniform vec4 u_data[29];

    // ......... DEFINES ..........
        #define view0 mat4(u_data[4], u_data[5], u_data[6], u_data[7])
        #define view1 mat4(u_data[8], u_data[9], u_data[10], u_data[11])
        #define view2 mat4(u_data[12], u_data[13], u_data[14], u_data[15])
        #define view3 mat4(u_data[16], u_data[17], u_data[18], u_data[19])
        #define view4 mat4(u_data[20], u_data[21], u_data[22], u_data[23])
        #define view5 mat4(u_data[24], u_data[25], u_data[26], u_data[27])

        out vec4 frag_pos;

        mat4 view_matrices[6];

        void main()
        {

            view_matrices[0] =  view0;
            view_matrices[1] =  view1;
            view_matrices[2] =  view2;
            view_matrices[3] =  view3;
            view_matrices[4] =  view4;
            view_matrices[5] =  view5;

            for(int face = 0; face < 6; ++face)
            {
                gl_Layer = face;
                for(int i = 0; i < 3; ++i) // for each triangle's vertices
                {
                    frag_pos = gl_in[i].gl_Position;
                    gl_Position = view_matrices[face] * frag_pos;
                    EmitVertex();
                }    
                EndPrimitive();
            }
        }  
  )GPOINTDEPTH";



  // -- (fragment) --
  static const char* point_shadow_depth_fragment_shader_ = R"FPOINTDEPTH(
    #version 330

// ......... UNIFORMS .........
    uniform vec4 u_data[29];

// ......... DEFINES ..........
    #define light_position u_data[28].xyz
    #define far_plane u_data[28].w

    in vec4 frag_pos;

    void main()
    {
        // get distance between fragment and light source
        float light_distance = length(frag_pos.xyz - light_position);
    
        // map to [0;1] range by dividing by far_plane
        light_distance = light_distance / far_plane;
    
        // write this as modified depth
        gl_FragDepth = light_distance;
    }  
  
  )FPOINTDEPTH";

  // ------------------------- PointShadowDepthShaders -------------------------- //

}

#endif // __POINT_SHADOW_DEPTH_SHADERS_H__