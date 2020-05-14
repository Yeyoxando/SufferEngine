// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __PHONG_SHADERS_H__
#define __PHONG_SHADERS_H__

namespace Suffer {

  // ---------------------------- PhongShaders ----------------------------- //

  // -- (vertex) --
  static const char* blinn_phong_vertex_shader = R"VBPHONGSHADER(
    #version 330

    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;
    
// ......... UNIFORMS .........
    uniform vec4 u_data[218];
    uniform vec4 u_material_data[4];

// ......... DEFINES ..........
    #define u_m_matrix mat4(u_data[0], u_data[1], u_data[2], u_data[3])

    #define u_v_matrix mat4(u_data[4], u_data[5], u_data[6], u_data[7])

    #define u_p_matrix mat4(u_data[8], u_data[9], u_data[10], u_data[11])

    #define u_time u_material_data[0].x

// ....... IN / OUT ........
    out vec3 position;
    out vec3 normal;
    out vec3 frag_pos;
    out vec2 uvs;
    out float time;

// ......... MAIN ..........
    void main(){  
      mat4 accum_matrix = u_p_matrix * u_v_matrix * u_m_matrix;

      //Normal is a CoVector and because of that we have to multiply by transponded inverse
      normal = normalize(mat3(transpose(inverse(u_m_matrix))) * vec4(a_normal, 0.0f).xyz); 
      frag_pos = (u_m_matrix * vec4(a_position, 1.0f)).xyz;
      uvs = a_uvs;
      time = u_time;
	    
      position = vec3(u_m_matrix * vec4(a_position, 1.0f));
      gl_Position = u_p_matrix * u_v_matrix * vec4(position, 1.0f);
    }
  
  )VBPHONGSHADER";

  
  // -- (fragment) --
  static const char* blinn_phong_fragment_shader = R"FBPHONGSHADER(
    #version 330

// ....... STRUCTS ........
    // DIRECTIONAL LIGHT
    struct DirectionalLight{
      vec3 specular;
      vec3 diffuse;
      vec3 ambient;
      vec3 color;
    
      vec3 direction;

      bool is_active;
      float intensity;

      mat4 view_projection_matrix;
    };

    // POINT LIGHT
    struct PointLight{
      vec3 specular;
      vec3 diffuse;
      vec3 ambient;
      vec3 color;
    
      vec3 position;

      bool is_active;
      float intensity;   

      float constant;
      float linear;
      float quadratic;

      mat4 view_projection_matrix[6];
    };

    // SPOT LIGHT
    struct SpotLight{
      vec3 specular;
      vec3 diffuse;
      vec3 ambient;
      vec3 color;
    
      vec3 position;
      vec3 direction;

      float constant;
      float linear;
      float quadratic;
      float cutOff;
      float outerCutOff;

      bool is_active;
      float intensity;      

      mat4 view_projection_matrix;
    };

// ......... UNIFORMS .........
    uniform vec4 u_data[218];
    uniform vec4 u_material_data[4];

    uniform sampler2D u_tex0;
    uniform sampler2D u_tex1; 
    uniform sampler2D u_tex2; 

    uniform samplerCube u_skybox;

    uniform sampler2D u_dir_light_texture0;
    uniform sampler2D u_dir_light_texture1;
    uniform sampler2D u_dir_light_texture2;
    uniform sampler2D u_dir_light_texture3;

    uniform samplerCube u_point_light_texture0;
    uniform samplerCube u_point_light_texture1;
    uniform samplerCube u_point_light_texture2;
    uniform samplerCube u_point_light_texture3;

    uniform sampler2D u_spot_light_texture0;
    uniform sampler2D u_spot_light_texture1;
    uniform sampler2D u_spot_light_texture2;
    uniform sampler2D u_spot_light_texture3;

// ......... DEFINES ..........
    #define u_color u_material_data[0]
    #define camera_pos vec3(u_material_data[1].x, u_material_data[1].y, u_material_data[1].z)
    #define u_tiling u_material_data[2].xy
    
    #define u_specular_strength u_material_data[2].z
    #define u_specular_pow u_material_data[2].w
    #define u_reflection_strength u_material_data[3].x

    #define max_lights 4
    #define num_lights u_data[12].x
    #define num_directionals u_data[12].y
    #define num_points u_data[12].z
    #define num_spots u_data[12].w
    
    #define u_albedo u_tex0
    #define u_specular u_tex1
    #define u_reflection u_tex2

// ....... IN / OUT ........
    in vec3 position;
    in vec3 normal;
    in vec3 frag_pos;
    in vec2 uvs;
    in float time;

    out vec4 fragColor;

// ....... FUNCTIONS ........
    // DIRECTIONALS
    DirectionalLight GetDirectionalLight(int index){
      DirectionalLight d_light;
      int offset = 9 * index;

      // 13 is start of directional lights array (52/4)
      d_light.is_active    = bool(u_data[13 + 0 + offset].a);
      d_light.direction = vec3(u_data[13 + 0 + offset].x, u_data[13 + 0 + offset].y, u_data[13 + 0 + offset].z);
      d_light.color     = vec3(u_data[13 + 1 + offset].x, u_data[13 + 1 + offset].y, u_data[13 + 1 + offset].z);
      d_light.intensity =      u_data[13 + 2 + offset].a;
      d_light.ambient   = vec3(u_data[13 + 2 + offset].x, u_data[13 + 2 + offset].y, u_data[13 + 2 + offset].z);
      d_light.diffuse   = vec3(u_data[13 + 3 + offset].x, u_data[13 + 3 + offset].y, u_data[13 + 3 + offset].z);
      d_light.specular  = vec3(u_data[13 + 4 + offset].x, u_data[13 + 4 + offset].y, u_data[13 + 4 + offset].z);

      // View-Projection Matrix
      d_light.view_projection_matrix = mat4(u_data[13 + offset + 5], 
                                            u_data[13 + offset + 6], 
                                            u_data[13 + offset + 7], 
                                            u_data[13 + offset + 8]);

      return d_light;
    }

    vec4 GetDirectionalLightTexture(int index, vec2 proj_coord){
      if(index == 0){
        return texture(u_dir_light_texture0, proj_coord.xy);
      }
      if(index == 1){
        return texture(u_dir_light_texture1, proj_coord.xy);
      }
      if(index == 2){
        return texture(u_dir_light_texture2, proj_coord.xy);
      }
      if(index == 3){
        return texture(u_dir_light_texture3, proj_coord.xy);
      }
    }

// --------------------------------------------------------------------- //

    // POINTS
    PointLight GetPointLight(int index){
      PointLight p_light;
      int offset = 30 * index;

      p_light.is_active    = bool(u_data[49 + 0 + offset].a);
      p_light.position  = vec3(u_data[49 + 0 + offset].x, u_data[49 + 0 + offset].y, u_data[49 + 0 + offset].z);
      p_light.color     = vec3(u_data[49 + 1 + offset].x, u_data[49 + 1 + offset].y, u_data[49 + 1 + offset].z);
      p_light.ambient   = vec3(u_data[49 + 2 + offset].x, u_data[49 + 2 + offset].y, u_data[49 + 2 + offset].z);
      p_light.intensity =      u_data[49 + 2 + offset].a;
      p_light.diffuse   = vec3(u_data[49 + 3 + offset].x, u_data[49 + 3 + offset].y, u_data[49 + 3 + offset].z);
      p_light.specular  = vec3(u_data[49 + 4 + offset].x, u_data[49 + 4 + offset].y, u_data[49 + 4 + offset].z);
      p_light.constant  =      u_data[49 + 5 + offset].x;
      p_light.linear    =      u_data[49 + 5 + offset].y;
      p_light.quadratic =      u_data[49 + 5 + offset].z;

      // View-Projection Matrices
      for(int f = 0; f < 6; f++){
        p_light.view_projection_matrix[f] = mat4(u_data[49 + 6 + offset + (4 * f)],   
                                                 u_data[49 + 7 + offset + (4 * f)], 
                                                 u_data[49 + 8 + offset + (4 * f)], 
                                                 u_data[49 + 9 + offset + (4 * f)]);
      }
      return p_light;
    }

    vec4 GetPointLightTexture(int index, vec3 frag_to_light){
      if(index == 0){
        return texture(u_point_light_texture0, frag_to_light);
      }
      if(index == 1){
        return texture(u_point_light_texture1, frag_to_light);
      }
      if(index == 2){
        return texture(u_point_light_texture2, frag_to_light);
      }
      if(index == 3){
        return texture(u_point_light_texture3, frag_to_light);
      }
    }

// --------------------------------------------------------------------- //

    // SPOTS
    SpotLight GetSpotLight(int index){
      SpotLight s_light;
      int offset = 12 * index;

      s_light.is_active    = bool(u_data[169 + 0 + offset].a);
      s_light.direction = vec3(u_data[169 + 0 + offset].x, u_data[169 + 0 + offset].y, u_data[169 + 0 + offset].z);
      s_light.position  = vec3(u_data[169 + 1 + offset].x, u_data[169 + 1 + offset].y, u_data[169 + 1 + offset].z);
      s_light.color     = vec3(u_data[169 + 2 + offset].x, u_data[169 + 2 + offset].y, u_data[169 + 2 + offset].z);
      s_light.intensity =      u_data[169 + 3 + offset].a;         
      s_light.ambient   = vec3(u_data[169 + 3 + offset].x, u_data[169 + 3 + offset].y, u_data[169 + 3 + offset].z);
      s_light.diffuse   = vec3(u_data[169 + 4 + offset].x, u_data[169 + 4 + offset].y, u_data[169 + 4 + offset].z);
      s_light.specular  = vec3(u_data[169 + 5 + offset].x, u_data[169 + 5 + offset].y, u_data[169 + 5 + offset].z);
      s_light.constant  =      u_data[169 + 6 + offset].x;
      s_light.linear    =      u_data[169 + 6 + offset].y;
      s_light.quadratic =      u_data[169 + 6 + offset].z;
      s_light.cutOff    =      u_data[169 + 7 + offset].x;
      s_light.outerCutOff =    u_data[169 + 7 + offset].y; 

      // View-Projection Matrix
      s_light.view_projection_matrix = mat4(u_data[169 + offset + 8], 
                                            u_data[169 + offset + 9], 
                                            u_data[169 + offset + 10], 
                                            u_data[169 + offset + 11]);
      return s_light;
    }

    vec4 GetSpotLightTexture(int index, vec2 proj_coord){
      if(index == 0){
        return texture(u_spot_light_texture0, proj_coord.xy);
      }
      if(index == 1){
        return texture(u_spot_light_texture1, proj_coord.xy);
      }
      if(index == 2){
        return texture(u_spot_light_texture2, proj_coord.xy);
      }
      if(index == 3){
        return texture(u_spot_light_texture3, proj_coord.xy);
      }
    }

// --------------------------------------------------------------------- //

    float CalculateShadow(vec4 frag_pos_light_space, vec3 light_dir, int light_index){
      // Clip projection coords
      vec3 proj_coords = frag_pos_light_space.xyz / frag_pos_light_space.w;
      // Convert from [-1, 1] to [0, 1]
      proj_coords = proj_coords * 0.5f + 0.5f;
      // Get shadow map fragment
      float closest_depth = GetDirectionalLightTexture(light_index, proj_coords.xy).r;
      // Current depth fragment from light perspective
      float current_depth = proj_coords.z;
      // Compare current and closest to check if its in shadow or not
      //float bias = 0.002f;
      float bias = max(0.003f * (1.0f - dot(normal, light_dir)), 0.001f);
      float shadow = (current_depth - bias) > closest_depth ? 1.0f : 0.0f;

      return shadow;
    }

// --------------------------------------------------------------------- //

    vec3 CalculateDirectionalLight(DirectionalLight light, int light_index, vec3 normal, vec3 view_dir){
      vec3 light_dir = normalize(-light.direction);
      
      float diff = max(dot(normal, light_dir), 0.0f);
      vec3 reflect_dir = reflect(-light_dir, normal);
      float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), u_specular_pow);

      vec3 ref_view_dir = normalize(position - camera_pos);      
      vec3 refle = reflect(ref_view_dir, normalize(normal)); 

      vec3 ambient  = light.ambient  * light.intensity * pow(texture(u_albedo, uvs * u_tiling).xyz, vec3(2.2f));
      vec3 diffuse  = light.diffuse  * light.intensity * diff * pow(texture(u_albedo, uvs * u_tiling).xyz, vec3(2.2f));
      vec3 specular = light.specular * light.intensity * (spec * u_specular_strength) * texture(u_specular, uvs * u_tiling).xyz;     
      float ref_value = texture(u_reflection, uvs * u_tiling).x * u_reflection_strength;
      vec3 reflection = (texture(u_skybox, refle).rgb * ref_value); 

      float shadow = CalculateShadow(light.view_projection_matrix * vec4(frag_pos, 1.0f), light_dir, light_index);

      float inv_reflection = (1.0f - ref_value);
      return (((ambient * inv_reflection) + reflection) + ((1.0f - shadow) * ((diffuse * inv_reflection) + specular))) * u_color.xyz;
    }

// --------------------------------------------------------------------- //

    float CalculatePointShadows(vec3 frag_pos, vec3 light_pos, vec3 light_dir, int light_index){
      vec3 fragToLight = frag_pos - light_pos;
      float closestDepth = GetPointLightTexture(light_index, fragToLight).r;
      closestDepth *= 100.0f; //  == FAR PLANE -> LOOK system_light
      float currentDepth = length(fragToLight);
      //float bias = 0.5f;
      float bias = max(0.5f * (1.0f - dot(normal, light_dir)), 0.4f);
      float shadow = currentDepth - bias > closestDepth ? 1.0f : 0.0f;

      return shadow;
    } 

// --------------------------------------------------------------------- //

    vec3 CalculatePointLight(PointLight light, int light_index, vec3 normal, vec3 view_dir) {
      vec3 light_dir = normalize(light.position - frag_pos);

      float diff = max(dot(light_dir, normal), 0.0f);

      vec3 halfway_dir = normalize(light_dir + view_dir);  
      float spec = pow(max(dot(normal, halfway_dir), 0.0f), u_specular_pow);

      vec3 ref_view_dir = normalize(position - camera_pos);      
      vec3 refle = reflect(ref_view_dir, normalize(normal));

      float distance    = length(light.position - frag_pos);
      float attenuation = 1.0f / (light.constant + light.linear * distance + 
  			       light.quadratic * distance); 

      vec3 ambient  = light.ambient * attenuation * light.intensity * pow(texture(u_albedo, uvs * u_tiling).xyz, vec3(2.2f));
      vec3 diffuse  = light.diffuse * attenuation * light.intensity * diff * pow(texture(u_albedo, uvs * u_tiling).xyz, vec3(2.2f));
      vec3 specular = light.specular* attenuation * light.intensity * (spec * u_specular_strength) * texture(u_specular, uvs * u_tiling).xyz;
      float ref_value = texture(u_reflection, uvs * u_tiling).x * u_reflection_strength;
      vec3 reflection = (texture(u_skybox, refle).rgb * ref_value); 

      float shadow = CalculatePointShadows(frag_pos, light.position, light_dir, light_index);

      float inv_reflection = (1.0f - ref_value);
      return (((ambient * inv_reflection) + reflection) + ((1.0f - shadow) * ((diffuse * inv_reflection) + specular))) * u_color.xyz;
    }

// --------------------------------------------------------------------- //

    float CalculateSpotShadow(vec4 frag_pos_light_space, vec3 light_dir, int light_index){
      // Clip projection coords
      vec3 proj_coords = frag_pos_light_space.xyz / frag_pos_light_space.w;
      // Convert from [-1, 1] to [0, 1]
      proj_coords = proj_coords * 0.5f + 0.5f;
      // Get shadow map fragment
      float closest_depth = GetSpotLightTexture(light_index, proj_coords.xy).r;
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

    vec3 CalculateSpotLight(SpotLight light, int light_index, vec3 normal) {
      vec3 norm = normalize(normal);
      vec3 light_dir = normalize(light.position - frag_pos);
      float diff = max(dot(norm, light_dir), 0.0f);

      vec3 view_dir = normalize(camera_pos - frag_pos);
      vec3 halfway_dir = normalize(light_dir + view_dir);  
      float spec = pow(max(dot(normal, halfway_dir), 0.0f), u_specular_pow);

      vec3 ref_view_dir = normalize(position - camera_pos);      
      vec3 refle = reflect(ref_view_dir, normalize(normal));

      float distance = length(light.position - frag_pos);
      float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic
        * distance);
    
      float theta = dot(light_dir, normalize(-light.direction));
      float epsilon = light.cutOff - light.outerCutOff;
      float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

      vec3 ambient  = light.ambient * attenuation * intensity * light.intensity * pow(texture(u_albedo, uvs * u_tiling).xyz, vec3(2.2f));
      vec3 diffuse  = light.diffuse * attenuation * intensity * light.intensity * diff * pow(texture(u_albedo, uvs * u_tiling).xyz, vec3(2.2f));
      vec3 specular = light.specular* attenuation * intensity * light.intensity * (spec * u_specular_strength) * texture(u_specular, uvs * u_tiling).xyz;
      float ref_value = texture(u_reflection, uvs * u_tiling).x * u_reflection_strength;
      vec3 reflection = (texture(u_skybox, refle).rgb * ref_value); 

      float shadow = CalculateSpotShadow(light.view_projection_matrix * vec4(frag_pos, 1.0f), light_dir, light_index);

      float inv_reflection = (1.0f - ref_value);
      return (((ambient * inv_reflection) + reflection) + ((1.0f - shadow) * ((diffuse * inv_reflection) + specular))) * u_color.xyz;
    }

// ......... MAIN ..........
    void main() {
      vec3 view_dir = normalize(camera_pos - frag_pos);

      vec3 directionals = vec3(0.0f, 0.0f, 0.0f);
      for(int i = 0; i < num_directionals; ++i){
        directionals += CalculateDirectionalLight(GetDirectionalLight(i), i, normal, view_dir) * float(GetDirectionalLight(i).is_active);
      }
 
      vec3 point = vec3(0.0f, 0.0f, 0.0f);
      for(int i = 0; i < num_points; ++i){
        point += CalculatePointLight(GetPointLight(i), i, normal, view_dir) * float(GetPointLight(i).is_active);
      }

      vec3 spot = vec3(0.0f, 0.0f, 0.0f);
      for(int i = 0; i < num_spots; ++i){
        spot += CalculateSpotLight(GetSpotLight(i), i, normal) * float(GetSpotLight(i).is_active);
      }

      fragColor = vec4((directionals + point + spot), 1.0f);
    }

  )FBPHONGSHADER";

  // ---------------------------- PhongShaders ----------------------------- //

}

#endif