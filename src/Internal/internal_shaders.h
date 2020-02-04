// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __INTERNAL_SHADERS_H__
#define __INTERNAL_SHADERS_H__

namespace Suffer {
  // ----------------------- RenderToTextureShaders ------------------------ //

  // -- Render to texture (vertex) --
  static const char* render_to_texture_vertex_ = R"VTOTEXTURE(
    #version 330
    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;

    uniform vec4 u_data[13];

    out vec2 tex_coords;

    void main()
    {
        gl_Position = vec4(a_position.x, a_position.y, 0.0, 1.0); 
        tex_coords = a_uvs;
    }  

  )VTOTEXTURE";

  // -- Render to texture (fragment) --
  static const char* render_to_texture_fragment_ = R"FTOTEXTURE(
    #version 330
    out vec4 FragColor;
      
    in vec2 tex_coords;
    
    uniform sampler2D u_tex0;
    
    void main()
    { 
        vec4 color = texture2D(u_tex0, tex_coords);
			  float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
			  FragColor = vec4(vec3(gray), 1.0);
        //FragColor = texture(u_tex0, tex_coords);
    }    

  )FTOTEXTURE";

  // ----------------------- RenderToTextureShaders ------------------------ //
  
  // --------------------------- DefaultShaders ---------------------------- //

  // -- Default vertex shader --
  static const char* default_vertex_shader_ = R"VDEFAULTSHADER(
    #version 330

    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;
    
    uniform vec4 u_data[13];

    #define model0 u_data[0]
    #define model1 u_data[1]
    #define model2 u_data[2]
    #define model3 u_data[3]

    #define view0 u_data[4]
    #define view1 u_data[5]
    #define view2 u_data[6]
    #define view3 u_data[7]

    #define projection0 u_data[8]
    #define projection1 u_data[9]
    #define projection2 u_data[10]
    #define projection3 u_data[11]

    #define u_color u_data[12]

    out vec4 color;
    out vec3 normal;
    out vec2 uvs;
    
    mat4 CompoundMatrix(vec4 vector1, vec4 vector2, vec4 vector3, vec4 vector4){
      return mat4(vector1, vector2, vector3, vector4);
    }

    void main(){
      mat4 u_m_matrix = CompoundMatrix(model0, model1, model2, model3);
      mat4 u_v_matrix = CompoundMatrix(view0, view1, view2, view3);
      mat4 u_p_matrix = CompoundMatrix(projection0, projection1, projection2, projection3);      

      mat4 accum_matrix = u_p_matrix * u_v_matrix * u_m_matrix;
      color = u_color;
      normal = normalize((accum_matrix * vec4(a_normal, 0.0))).xyz;
      uvs = a_uvs;
	    gl_Position = accum_matrix * vec4(a_position, 1.0f);
    }

    )VDEFAULTSHADER";


  // -- Default fragment shader --
  static const char* default_fragment_shader_ = R"FSHADER(
    #version 330

    out vec4 fragColor;

    uniform sampler2D u_tex0;
    //uniform sampler2D u_tex1;
    //uniform sampler2D u_tex2;
    //uniform sampler2D u_texn;

    #define u_albedo u_tex0

    in vec4 color;
    in vec3 normal;
    in vec2 uvs;

    vec3 light_dir = vec3(0, 0, 1);
    vec3 light_color = vec3(1, 1, 1);

    // --------------------------------------------------------------------- //

    vec3 CreateDiffuseLight(vec3 light_direction) {

      vec3 norm = normalize(normal);
      float diffs = max(dot(norm, -light_direction), 0.0f);
      vec3 diffuse_light = diffs * vec3(light_color) * 0.4;

      return diffuse_light;
    }

    // --------------------------------------------------------------------- //

    void main() {

      // Texture
      vec4 tex_color = texture(u_albedo, uvs) * color;

      // Ambient
      vec3 ambient = 0.4 * light_color;

      // Diffuse
      float diff = max(dot(normalize(normal), normalize(-light_dir)), 0.0);
      vec3 test = CreateDiffuseLight(light_dir);
      vec3 color_result = (ambient + test) * tex_color.xyz;

      fragColor = vec4(color_result, 1.0f);
    }

  )FSHADER";

  // --------------------------- DefaultShaders ---------------------------- //

  // --------------------------- UnlitShaders ---------------------------- //

  static const char* unlit_vertex_shader = R"VUNLITSHADER(
  

    #version 330

    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;
    
    uniform vec4 u_data[14];

    #define model0 u_data[0]
    #define model1 u_data[1]
    #define model2 u_data[2]
    #define model3 u_data[3]

    #define view0 u_data[4]
    #define view1 u_data[5]
    #define view2 u_data[6]
    #define view3 u_data[7]

    #define projection0 u_data[8]
    #define projection1 u_data[9]
    #define projection2 u_data[10]
    #define projection3 u_data[11]

    #define u_color u_data[12]

    #define u_time u_data[13].x

    out vec4 color;
    out vec3 normal;
    out vec2 uvs;
    out float time;
    
    mat4 CompoundMatrix(vec4 vector1, vec4 vector2, vec4 vector3, vec4 vector4){
      return mat4(vector1, vector2, vector3, vector4);
    }

    void main(){
      mat4 u_m_matrix = CompoundMatrix(model0, model1, model2, model3);
      mat4 u_v_matrix = CompoundMatrix(view0, view1, view2, view3);
      mat4 u_p_matrix = CompoundMatrix(projection0, projection1, projection2, projection3);      

      mat4 accum_matrix = u_p_matrix * u_v_matrix * u_m_matrix;
      color = u_color;
      normal = normalize((accum_matrix * vec4(a_normal, 0.0))).xyz;
      uvs = a_uvs;
      time = u_time;
	    gl_Position = accum_matrix * vec4(a_position, 1.0f);
    }
  
  )VUNLITSHADER";

  static const char* unlit_fragment_shader = R"FUNLITSHADER(
  
    #version 330

    out vec4 fragColor;

    in vec4 color;
    in vec3 normal;
    in vec2 uvs;
    in float time;

    vec3 light_dir = vec3(0, 0, 1);
    vec3 light_color = vec3(1, 1, 1);

    // --------------------------------------------------------------------- //

    vec3 CreateDiffuseLight(vec3 light_direction) {

      vec3 norm = normalize(normal);
      float diffs = max(dot(norm, -light_direction), 0.0f);
      vec3 diffuse_light = diffs * vec3(light_color) * 0.4;

      return diffuse_light;
    }

    // --------------------------------------------------------------------- //

    void main() {

      // Ambient
      vec3 ambient = 0.4 * light_color * color.xyz;

      // Diffuse
      float diff = max(dot(normalize(normal), normalize(-light_dir)), 0.0);
      vec3 test = CreateDiffuseLight(light_dir);

      fragColor = vec4(ambient * abs(sin(time)), 1.0f);
    }

  )FUNLITSHADER";

  // --------------------------- UnlitShaders ---------------------------- //

}

#endif // __INTERNAL_SHADERS_H__
