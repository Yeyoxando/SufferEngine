// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __DEFAULT_SHADERS_H__
#define __DEFAULT_SHADERS_H__

namespace Suffer {

  // --------------------------- DefaultShaders ---------------------------- //

  // -- (vertex) --
  static const char* default_vertex_shader_ = R"VDEFAULTSHADER(
    #version 330

    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;
    
// ......... UNIFORMS .........
    uniform vec4 u_data[135];

// ......... DEFINES ..........
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

// ....... IN / OUT ........
    out vec4 color;
    out vec3 normal;
    out vec3 frag_pos;
    out vec2 uvs;
    out float time;


// ......... MAIN ..........
    void main(){
      mat4 u_m_matrix = mat4(model0, model1, model2, model3);
      mat4 u_v_matrix = mat4(view0, view1, view2, view3);
      mat4 u_p_matrix = mat4(projection0, projection1, projection2, projection3);    

      mat4 accum_matrix = u_p_matrix * u_v_matrix * u_m_matrix;

      color = u_color;
      normal = normalize((accum_matrix * vec4(a_normal, 0.0))).xyz;
      frag_pos = (u_m_matrix * vec4(a_position, 1.0f)).xyz;
      uvs = a_uvs;
      time = u_time;

	    gl_Position = accum_matrix * vec4(a_position, 1.0f);
    }

    )VDEFAULTSHADER";


  // -- (fragment) --
  static const char* default_fragment_shader_ = R"FSHADER(
    #version 330
 
// ....... STRUCTS ........
    struct DirectionalLight{
      vec3 direction;
    
      vec3 specular;
      vec3 diffuse;
      vec3 ambient;
      vec3 color;

      mat4 view_projection_matrix;
      int light_tex_pos;

      float intensity;

    };

    struct PointLight{
      vec3 position;

      vec3 specular;
      vec3 diffuse;
      vec3 ambient;
      vec3 color;

      float constant;
      float linear;
      float quadratic;

      mat4 view_projection_matrix[6];
      int light_tex_pos;

      float intensity;      

    };

    struct SpotLight{
      vec3 direction;
      vec3 position;
      float cutOff;
      float outerCutOff;

      vec3 specular;
      vec3 diffuse;
      vec3 ambient;
      vec3 color;

      float constant;
      float linear;
      float quadratic;

      mat4 view_projection_matrix;
      int light_tex_pos;

      float intensity;      

    };

// ......... UNIFORMS .........
    uniform vec4 u_data[135];
    uniform sampler2D u_tex0;
    uniform sampler2D u_tex1;   

    #define max_lights 4
    uniform sampler2D u_light_textures[max_lights];

// ......... DEFINES ..........
    #define camera_pos vec3(u_data[13].x, u_data[13].y, u_data[13].z)
    #define num_lights u_data[14].x

    #define start 15

    #define u_albedo u_tex0
    #define u_specular u_tex1

// ....... IN / OUT ........
    in vec4 color;
    in vec3 normal;
    in vec3 frag_pos;
    in vec2 uvs;
    in float time;

    out vec4 fragColor;

// ....... VARIABLES ........
    int num_directionals = 0;
    int num_points = 0;
    int num_spots = 0;

    DirectionalLight directional_lights[max_lights];
    PointLight point_lights[max_lights];
    SpotLight spot_lights[max_lights];

// ....... FUNCTIONS ........
    void CompoundLights(){
      int offset = 0;
      for(int i = 0; i < num_lights; ++i){
        switch(int(u_data[16 + (offset)].a)){
          case 0:
            DirectionalLight d_light;

            d_light.direction = vec3(u_data[start + 0 + (offset)].x, u_data[start + 0 + (offset)].y, u_data[start + 0 + (offset)].z);
            d_light.color     = vec3(u_data[start + 1 + (offset)].x, u_data[start + 1 + (offset)].y, u_data[start + 1 + (offset)].z);
            d_light.intensity = u_data[start + 2 + offset].a;
            d_light.ambient   = vec3(u_data[start + 2 + (offset)].x, u_data[start + 2 + (offset)].y, u_data[start + 2 + (offset)].z);
            d_light.diffuse   = vec3(u_data[start + 3 + (offset)].x, u_data[start + 3 + (offset)].y, u_data[start + 3 + (offset)].z);
            d_light.specular  = vec3(u_data[start + 4 + (offset)].x, u_data[start + 4 + (offset)].y, u_data[start + 4 + (offset)].z);

            // View-Projection Matrix
            d_light.view_projection_matrix = mat4(u_data[start + offset + 5], 
                                                  u_data[start + offset + 6], 
                                                  u_data[start + offset + 7], 
                                                  u_data[start + offset + 8]);
            
            d_light.light_tex_pos = i;

            directional_lights[num_directionals] = d_light;
            num_directionals++;
            offset += 9;
            break;
          case 1:
            PointLight p_light;
            p_light.position  = vec3(u_data[start + 0 + (offset)].x, u_data[start + 0 + (offset)].y, u_data[start + 0 + (offset)].z);
            p_light.color     = vec3(u_data[start + 1 + (offset)].x, u_data[start + 1 + (offset)].y, u_data[start + 1 + (offset)].z);
            p_light.ambient   = vec3(u_data[start + 2 + (offset)].x, u_data[start + 2 + (offset)].y, u_data[start + 2 + (offset)].z);
            p_light.diffuse   = vec3(u_data[start + 3 + (offset)].x, u_data[start + 3 + (offset)].y, u_data[start + 3 + (offset)].z);
            p_light.specular  = vec3(u_data[start + 4 + (offset)].x, u_data[start + 4 + (offset)].y, u_data[start + 4 + (offset)].z);
            p_light.constant  = u_data[start + 5 + (offset)].x;
            p_light.linear    = u_data[start + 5 + (offset)].y;
            p_light.quadratic = u_data[start + 5 + (offset)].z;
            p_light.intensity = u_data[start + 2 + offset].a;

            // View-Projection Matrices
            for(int f = 0; f < 6; f++){
              d_light.view_projection_matrix = mat4(u_data[start + offset + 5 + (4 * f)],   
                                                    u_data[start + offset + 6 + (4 * f)], 
                                                    u_data[start + offset + 7 + (4 * f)], 
                                                    u_data[start + offset + 8 + (4 * f)]);
            }

            point_lights[num_points] = p_light;
            num_points++;
            offset += 30;
            break;
          case 2:
            SpotLight s_light;
            s_light.direction = vec3(u_data[start + 0 + (offset)].x, u_data[start + 0 + (offset)].y, u_data[start + 0 + (offset)].z);
            s_light.position  = vec3(u_data[start + 1 + (offset)].x, u_data[start + 1 + (offset)].y, u_data[start + 1 + (offset)].z);
            s_light.color     = vec3(u_data[start + 2 + (offset)].x, u_data[start + 2 + (offset)].y, u_data[start + 2 + (offset)].z);
            s_light.intensity = u_data[start + 3 + offset].a;         
            s_light.ambient   = vec3(u_data[start + 3 + (offset)].x, u_data[start + 3 + (offset)].y, u_data[start + 3 + (offset)].z);
            s_light.diffuse   = vec3(u_data[start + 4 + (offset)].x, u_data[start + 4 + (offset)].y, u_data[start + 4 + (offset)].z);
            s_light.specular  = vec3(u_data[start + 5 + (offset)].x, u_data[start + 5 + (offset)].y, u_data[start + 5 + (offset)].z);
            s_light.constant  = u_data[start + 6 + (offset)].x;
            s_light.linear    = u_data[start + 6 + (offset)].y;
            s_light.quadratic = u_data[start + 6 + (offset)].z;
            s_light.cutOff    = u_data[start + 7 + (offset)].x;
            s_light.outerCutOff = u_data[start + 7 + (offset)].y; 

            // View-Projection Matrix
            d_light.view_projection_matrix = mat4(u_data[start + offset + 8], 
                                                  u_data[start + offset + 9], 
                                                  u_data[start + offset + 10], 
                                                  u_data[start + offset + 11]);
  
            spot_lights[num_spots] = s_light;
            num_spots++;
            offset += 12;
            break;
        }
      }
    }

    // --------------------------------------------------------------------- //

    float CalculateShadow(vec4 frag_pos_light_space, vec3 light_dir, int shadow_map_pos){
      // Clip projection coords
      vec3 proj_coords = frag_pos_light_space.xyz / frag_pos_light_space.w;
      // Convert from [-1, 1] to [0, 1]
      proj_coords = proj_coords * 0.5f + 0.5;
      // Get shadow map fragment
      float closest_depth = texture(u_light_textures[shadow_map_pos], proj_coords.xy).r;
      // Current depth fragment from light perspective
      float current_depth = proj_coords.z;
      // Compare current and closest to check if its in shadow or not
      //float bias = 0.002f;
      float bias = max(0.002f * (1.0f - dot(normal, light_dir)), 0.001f);
      //float shadow = current_depth > closest_depth ? 1.0f : 0.0f;
      float shadow = (current_depth - bias) > closest_depth ? 1.0f : 0.0f;

      return shadow;
    }

    // --------------------------------------------------------------------- //

    vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_dir){
  
      vec3 light_dir = normalize(-light.direction);
      
      float diff = max(dot(normal, light_dir), 0.0f);
      vec3 reflect_dir = reflect(-light_dir, normal);
      float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), 32);

      vec3 ambient  = light.ambient  * light.intensity * texture(u_albedo, uvs).xyz;
      vec3 diffuse  = light.diffuse  * light.intensity * diff * texture(u_albedo, uvs).xyz;
      vec3 specular = light.specular * light.intensity * spec * texture(u_specular, uvs).xyz;
      
      float shadow = CalculateShadow(light.view_projection_matrix * vec4(frag_pos, 1.0f), light_dir, light.light_tex_pos);

      return (ambient + (1.0 - shadow) * (diffuse + specular));

    }

    // --------------------------------------------------------------------- //

    vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 view_dir) {

      vec3 light_dir = normalize(light.position - frag_pos);

      float diff = max(dot(normal, light_dir), 0.0);

      vec3 reflect_dir = reflect(-light_dir, normal);
      float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);

      float distance    = length(light.position - frag_pos);
      float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			       light.quadratic * (distance * distance));    

      vec3 ambient  = light.ambient ;
      vec3 diffuse  = light.diffuse ;
      vec3 specular = light.specular;
      ambient  *= attenuation * light.intensity * texture(u_albedo, uvs).xyz;
      diffuse  *= attenuation * light.intensity * diff * texture(u_albedo, uvs).xyz;
      specular *= attenuation * light.intensity * spec * texture(u_specular, uvs).xyz;

      return (ambient + diffuse + specular);

    }

    // --------------------------------------------------------------------- //

    vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 view_dir) {

      vec3 ambient = light.ambient * texture(u_albedo, uvs).xyz;
    
      vec3 norm = normalize(normal);
      vec3 light_dir = normalize(light.position - frag_pos);
      float diff = max(dot(norm, light_dir), 0.0f);
      vec3 diffuse = light.diffuse * diff * texture(u_albedo, uvs).xyz;

      vec3 reflect_dir = reflect(-light.direction, norm);
      float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), 32);
      vec3 specular = light.specular * spec * texture(u_specular, uvs).xyz;

      float distance = length(light.position - frag_pos);
      float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic
        * (distance * distance));
    
      float theta = dot(light_dir, normalize(-light.direction));
      float epsilon = light.cutOff - light.outerCutOff;
      float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

      ambient  *= intensity * light.intensity;
      diffuse  *= intensity * light.intensity;
      specular *= intensity * light.intensity;

      return (ambient + diffuse + specular);
      
    }


// ......... MAIN ..........
    void main() {
      CompoundLights();

      vec3 view_dir = normalize(camera_pos - frag_pos);

      vec3 directionals = vec3(0.0f, 0.0f, 0.0f);
      for(int i = 0; i < num_directionals; ++i){
        directionals += CalculateDirectionalLight(directional_lights[i], normal, view_dir);
      }
       
      vec3 point = vec3(0.0f, 0.0f, 0.0f);
      for(int i = 0; i < num_points; ++i){
        point += CalculatePointLight(point_lights[i], normal, view_dir);
      }
       
      vec3 spot = vec3(0.0f, 0.0f, 0.0f);
      for(int i = 0; i < num_spots; ++i){
        spot += CalculateSpotLight(spot_lights[i], normal, view_dir);
      }

      vec3 result = directionals + point + spot;
      
      fragColor = vec4(result, 1.0f);
    }

  )FSHADER";

  // --------------------------- DefaultShaders ---------------------------- //

}

#endif