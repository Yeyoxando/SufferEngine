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


  // WARNING!! This has to be the last rendered shader because of gamma correction
  // -- (fragment) --
  static const char* render_to_texture_fragment_ = R"FTOTEXTURE(
    #version 330

// ....... IN / OUT ........
    in vec2 tex_coords;
      
    out vec4 FragColor;
    
// ......... UNIFORMS .........
    uniform sampler2D u_tex0;
    
// ......... MAIN ..........
    void main(){
      // Final gamma correction only applied in this final shader 
      float gamma = 2.2f;
      FragColor.xyz = pow(texture(u_tex0, tex_coords).xyz, vec3(1.0f/gamma));
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


  // ------------------------ BRGA ------------------------- //
  // -- (vertex) --
  static const char* brga_vertex_ = R"VBRGA(
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

  )VBRGA";


  // -- (fragment) --
  static const char* brga_fragment_ = R"FBRGA(
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
        FragColor = color.brga;

    }    

  )FBRGA";

  // ------------------------ BRGA ------------------------- //

  // ------------------------ RBGA ------------------------- //
  // -- (vertex) --
  static const char* rbga_vertex_ = R"VRBGA(
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

  )VRBGA";


  // -- (fragment) --
  static const char* rbga_fragment_ = R"FRBGA(
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
        FragColor = color.rbga;

    }    

  )FRBGA";

  // ------------------------ RBGA ------------------------- //

  // ------------------------ ARBG ------------------------- //
  // -- (vertex) --
  static const char* argb_vertex_ = R"VARBG(
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

  )VARBG";


  // -- (fragment) --
  static const char* argb_fragment_ = R"FARBG(
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
        FragColor = color.arbg;

    }    

  )FARBG";

  // ------------------------ ARBG ------------------------- //

  // ------------------------ GBRA ------------------------- //
  // -- (vertex) --
  static const char* gbra_vertex_ = R"VGBRA(
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

  )VGBRA";


  // -- (fragment) --
  static const char* gbra_fragment_ = R"FGBRA(
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
        FragColor = color.gbra;

    }    

  )FGBRA";

  // ------------------------ GBRA ------------------------- //

  // ------------------------ INVCOLORS ------------------------- //
  // -- (vertex) --
  static const char* invcolors_vertex_ = R"VINVCOLORS(
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

  )VINVCOLORS";


  // -- (fragment) --
  static const char* invcolors_fragment_ = R"FINVCOLORS(
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
        FragColor = vec4(1.0 - color.r, 1.0 - color.g, 1.0 - color.b, 1);

    }    

  )FINVCOLORS";

  // ------------------------ INVCOLORS ------------------------- //

  // ------------------------ Blur ------------------------- //
  // -- (vertex) --
  static const char* blur_vertex_ = R"VBLUR(
    #version 330
    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;

// ....... IN / OUT ........
    out vec2 tex_coords;
    out vec2 blurTextureCoords[11];

// ......... MAIN ..........
    void main()
    {
	      vec2 centerTexCoords = a_position.xy * 0.5 + 0.5;
        float pixelSize = 1.0 / 700.0f;

	      //Horizontal blur
	      for(int i = -5; i <= 5; ++i){
		      blurTextureCoords[i + 5] = centerTexCoords + vec2(pixelSize * i, 0.0);
	      }

        gl_Position = vec4(a_position.x, a_position.y, 0.0f, 1.0f); 
        tex_coords = a_uvs;
    }  

  )VBLUR";


  // -- (fragment) --
  static const char* blur_fragment_ = R"FBLUR(
    #version 330

// ....... IN / OUT ........
    in vec2 tex_coords;
    in vec2 blurTextureCoords[11];
    out vec4 FragColor;
    
// ......... UNIFORMS .........
    uniform sampler2D u_tex0;
    
// ......... MAIN ..........
    void main()
    { 
    
        FragColor += texture2D(u_tex0, blurTextureCoords[1]) * 0.028002;
        FragColor += texture2D(u_tex0, blurTextureCoords[2]) * 0.065984;
        FragColor += texture2D(u_tex0, blurTextureCoords[3]) * 0.121703;
        FragColor += texture2D(u_tex0, blurTextureCoords[4]) * 0.175713;
        FragColor += texture2D(u_tex0, blurTextureCoords[5]) * 0.198596;
        FragColor += texture2D(u_tex0, blurTextureCoords[6]) * 0.175713;
        FragColor += texture2D(u_tex0, blurTextureCoords[7]) * 0.121703;
        FragColor += texture2D(u_tex0, blurTextureCoords[8]) * 0.065984;
        FragColor += texture2D(u_tex0, blurTextureCoords[9]) * 0.028002;
        FragColor += texture2D(u_tex0, blurTextureCoords[10]) * 0.0093;

    }    

  )FBLUR";

  // ------------------------ Blur ------------------------- //

  // ------------------------ Contrast ------------------------- //
  // -- (vertex) --
  static const char* contrast_vertex_ = R"VCONTRAST(
    #version 330
    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;

// ....... IN / OUT ........
    out vec2 tex_coords;
    out vec2 blurTextureCoords[11];

// ......... MAIN ..........
    void main()
    {
	      vec2 centerTexCoords = a_position.xy * 0.5 + 0.5;
        float pixelSize = 1.0 / 700.0f;

	      //Horizontal blur
	      for(int i = -5; i <= 5; ++i){
		      blurTextureCoords[i + 5] = centerTexCoords + vec2(pixelSize * i, 0.0);
	      }

        gl_Position = vec4(a_position.x, a_position.y, 0.0f, 1.0f); 
        tex_coords = a_uvs;
    }  

  )VCONTRAST";


  // -- (fragment) --
  static const char* contrast_fragment_ = R"FCONTRAST(
    #version 330

// ....... IN / OUT ........
    in vec2 tex_coords;
    in vec2 blurTextureCoords[11];
    out vec4 FragColor;
    
// ......... UNIFORMS .........
    uniform sampler2D u_tex0;
    
// ......... MAIN ..........
    void main()
    { 
    
        vec4 color = texture2D(u_tex0, tex_coords);
        FragColor = (color - 0.5) * (1 + 0.3) + 0.5;

    }    

  )FCONTRAST";

  // ------------------------ Blur ------------------------- //


}

#endif