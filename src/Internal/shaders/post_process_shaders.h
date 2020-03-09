// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __POST_PROCESS_SHADERS_H__
#define __POST_PROCESS_SHADERS_H__

namespace Suffer {

  // ----------------------- RenderToTextureShaders ------------------------ //
  // -- (vertex) --
  static const char* render_to_texture_vertex_ = R"VTOTEXTURE(
    #version 330
    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;

// ....... IN / OUT ........
    out vec2 tex_coords;

// ......... MAIN ..........
    void main()
    {
        gl_Position = vec4(a_position.x, a_position.y, 0.0f, 1.0f); 
        tex_coords = a_uvs;
    }  

  )VTOTEXTURE";


  // -- (fragment) --
  static const char* render_to_texture_fragment_ = R"FTOTEXTURE(
    #version 330

// ....... IN / OUT ........
    in vec2 tex_coords;
      
    out vec4 FragColor;
    
// ......... UNIFORMS .........
    uniform sampler2D u_tex0;
    
// ......... MAIN ..........
    void main()
    { 
        FragColor = texture(u_tex0, tex_coords);
    }    

  )FTOTEXTURE";

  // ----------------------- RenderToTextureShaders ------------------------ //



  // ------------------------ BlackAndWhiteShaders ------------------------- //
  // -- (vertex) --
  static const char* black_and_white_vertex_ = R"VBLACKWHITE(
    #version 330
    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;

// ....... IN / OUT ........
    out vec2 tex_coords;

// ......... MAIN ..........
    void main()
    {
        gl_Position = vec4(a_position.x, a_position.y, 0.0f, 1.0f); 
        tex_coords = a_uvs;
    }  

  )VBLACKWHITE";


  // -- (fragment) --
  static const char* black_and_white_fragment_ = R"FBLACKWHITE(
    #version 330

// ....... IN / OUT ........
    in vec2 tex_coords;
      
    out vec4 FragColor;
    
// ......... UNIFORMS .........
    uniform sampler2D u_tex0;
    
// ......... MAIN ..........
    void main()
    { 
        vec4 color = texture2D(u_tex0, tex_coords);
			  float gray = dot(color.rgb, vec3(0.299f, 0.587f, 0.114f));
			  FragColor = vec4(vec3(gray), 1.0f);
    }    

  )FBLACKWHITE";

  // ------------------------ BlackAndWhiteShaders ------------------------- //

}

#endif