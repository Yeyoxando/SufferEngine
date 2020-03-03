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
        FragColor = texture(u_tex0, tex_coords);
    }    

  )FTOTEXTURE";

  // -- Render to texture (vertex) --
  static const char* black_and_white_vertex_ = R"VBLACKWHITE(
    #version 330
    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;

    out vec2 tex_coords;

    void main()
    {
        gl_Position = vec4(a_position.x, a_position.y, 0.0, 1.0); 
        tex_coords = a_uvs;
    }  

  )VBLACKWHITE";

  // -- Render to texture (fragment) --
  static const char* black_and_white_fragment_ = R"FBLACKWHITE(
    #version 330
    out vec4 FragColor;
      
    in vec2 tex_coords;
    
    uniform sampler2D u_tex0;
    
    void main()
    { 
        vec4 color = texture2D(u_tex0, tex_coords);
			  float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
			  FragColor = vec4(vec3(gray), 1.0);
    }    

  )FBLACKWHITE";

  // ----------------------- RenderToTextureShaders ------------------------ //

  // ------------------------- ShadowDepthShaders -------------------------- //

  static const char* shadow_depth_vertex_shader_ = R"VSHADOWDEPTH(
    #version 330

    layout(location = 0) in vec3 a_position;
    
    uniform vec4 u_data[12];

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
    
    mat4 CompoundMatrix(vec4 vector1, vec4 vector2, vec4 vector3, vec4 vector4){
      return mat4(vector1, vector2, vector3, vector4);
    }

    void main(){
      mat4 u_m_matrix = CompoundMatrix(model0, model1, model2, model3);
      mat4 u_v_matrix = CompoundMatrix(view0, view1, view2, view3);
      mat4 u_p_matrix = CompoundMatrix(projection0, projection1, projection2, projection3); 

      mat4 accum_matrix = u_p_matrix * u_v_matrix * u_m_matrix;

	    gl_Position = accum_matrix * vec4(a_position, 1.0f);
    }  
  
  )VSHADOWDEPTH";

  static const char* shadow_depth_fragment_shader_ = R"FSHADOWDEPTH(
    #version 330

    void main(){
      //Do nothing because normally draws depth buffer itself
    }
  
  )FSHADOWDEPTH";

  // ------------------------- ShadowDepthShaders -------------------------- //

  // --------------------------- DefaultShaders ---------------------------- //

  // -- Default vertex shader --
  static const char* default_vertex_shader_ = R"VDEFAULTSHADER(
    #version 330

    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;
    
    uniform vec4 u_data[47];

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
    out vec3 fragPos;
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
      fragPos = (u_m_matrix * vec4(a_position, 1.0f)).xyz;
      normal = normalize((accum_matrix * vec4(a_normal, 0.0))).xyz;
      uvs = a_uvs;
      time = u_time;
	    gl_Position = accum_matrix * vec4(a_position, 1.0f);

    }

    )VDEFAULTSHADER";


  // -- Default fragment shader --
  static const char* default_fragment_shader_ = R"FSHADER(
    #version 330
 
    struct DirectionalLight{
      vec3 direction;
    
      vec3 specular;
      vec3 diffuse;
      vec3 ambient;
      vec3 color;

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

      float intensity;      

    };

    uniform vec4 u_data[47];
    uniform sampler2D u_tex0;
    uniform sampler2D u_tex1;
    uniform sampler2D u_tex2;

    #define camera_pos vec3(u_data[13].x, u_data[13].y, u_data[13].z)
    #define num_lights u_data[14].x
    #define u_albedo u_tex0
    #define u_specular u_tex1
    #define u_shadow_map u_tex2
    #define max_lights 4

    out vec4 fragColor;

    in vec4 color;
    in vec3 normal;
    in vec3 fragPos;
    in vec2 uvs;
    in float time;

    int num_directionals = 0;
    int num_points = 0;
    int num_spots = 0;
    
    DirectionalLight directional_lights[max_lights];
    PointLight point_lights[max_lights];
    SpotLight spot_lights[max_lights];

    // --------------------------------------------------------------------- //

    float CalculateShadow(vec4 frag_pos_light_space){
      // Clip projection coords
      vec3 proj_coords = frag_pos_light_space.xyz / frag_pos_light_space.w;
      // Convert from [-1, 1] to [0, 1]
      proj_coords = proj_coords * 0.5f + 0.5;
      // Get shadow map fragment
      float closest_depth = texture(u_shadow_map, proj_coords.xy).r;
      // Current depth fragment from light perspective
      float current_depth = proj_coords.z;
      // Compare current and closest to check if its in shadow or not
      float shadow = current_depth > closest_depth ? 1.0f : 0.0f;

      return shadow;

      //Final color later in fragment = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    }

    // --------------------------------------------------------------------- //

    void CompoundLights(){
      int offset = 0;
      for(int i = 0; i < num_lights; ++i){
        switch(int(u_data[16 + (offset)].a)){
          case 0:
            DirectionalLight d_light;
            d_light.direction = vec3(u_data[15 + (offset)].x, u_data[15 + (offset)].y, u_data[15 + (offset)].z);
            d_light.color     = vec3(u_data[16 + (offset)].x, u_data[16 + (offset)].y, u_data[16 + (offset)].z);
            d_light.ambient   = vec3(u_data[17 + (offset)].x, u_data[17 + (offset)].y, u_data[17 + (offset)].z);
            d_light.diffuse   = vec3(u_data[18 + (offset)].x, u_data[18 + (offset)].y, u_data[18 + (offset)].z);
            d_light.specular  = vec3(u_data[19 + (offset)].x, u_data[19 + (offset)].y, u_data[19 + (offset)].z);
            d_light.intensity = u_data[17 + offset].a;
            directional_lights[num_directionals] = d_light;
            num_directionals++;
            offset += 5;
            break;
          case 1:
            PointLight p_light;
            p_light.position  = vec3(u_data[15 + (offset)].x, u_data[15 + (offset)].y, u_data[15 + (offset)].z);
            p_light.color     = vec3(u_data[16 + (offset)].x, u_data[16 + (offset)].y, u_data[16 + (offset)].z);
            p_light.ambient   = vec3(u_data[17 + (offset)].x, u_data[17 + (offset)].y, u_data[17 + (offset)].z);
            p_light.diffuse   = vec3(u_data[18 + (offset)].x, u_data[18 + (offset)].y, u_data[18 + (offset)].z);
            p_light.specular  = vec3(u_data[19 + (offset)].x, u_data[19 + (offset)].y, u_data[19 + (offset)].z);
            p_light.constant  = u_data[20 + (offset)].x;
            p_light.linear    = u_data[20 + (offset)].y;
            p_light.quadratic = u_data[20 + (offset)].z;
            p_light.intensity = u_data[17 + offset].a;
            point_lights[num_points] = p_light;
            num_points++;
            offset += 6;
            break;
          case 2:
            SpotLight s_light;
            s_light.direction = vec3(u_data[15 + (offset)].x, u_data[15 + (offset)].y, u_data[15 + (offset)].z);
            s_light.position  = vec3(u_data[16 + (offset)].x, u_data[16 + (offset)].y, u_data[16 + (offset)].z);
            s_light.color     = vec3(u_data[17 + (offset)].x, u_data[17 + (offset)].y, u_data[17 + (offset)].z);
            s_light.ambient   = vec3(u_data[18 + (offset)].x, u_data[18 + (offset)].y, u_data[18 + (offset)].z);
            s_light.diffuse   = vec3(u_data[19 + (offset)].x, u_data[19 + (offset)].y, u_data[19 + (offset)].z);
            s_light.specular  = vec3(u_data[20 + (offset)].x, u_data[20 + (offset)].y, u_data[20 + (offset)].z);
            s_light.constant  = u_data[21 + (offset)].x;
            s_light.linear    = u_data[21 + (offset)].y;
            s_light.quadratic = u_data[21 + (offset)].z;            
            s_light.cutOff    = u_data[22 + (offset)].x;            
            s_light.outerCutOff = u_data[22 + (offset)].y; 
            s_light.intensity = u_data[18 + offset].a;           
            spot_lights[num_spots] = s_light;
            num_spots++;
            offset += 8;
            break;
        }
      }
    }

    // --------------------------------------------------------------------- //

    vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir){
  
      vec3 lightDir = normalize(-light.direction);
      
      float diff = max(dot(normal, lightDir), 0.0f);
      vec3 reflectDir = reflect(-lightDir, normal);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);

      vec3 ambient  = light.ambient  * light.intensity * texture(u_albedo, uvs).xyz;
      vec3 diffuse  = light.diffuse  * light.intensity * diff * texture(u_albedo, uvs).xyz;
      vec3 specular = light.specular * light.intensity * spec * texture(u_specular, uvs).xyz;

      return (ambient + diffuse + specular);

    }

    // --------------------------------------------------------------------- //

    vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDir) {

      vec3 lightDir = normalize(light.position - fragPos);

      float diff = max(dot(normal, lightDir), 0.0);

      vec3 reflectDir = reflect(-lightDir, normal);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

      float distance    = length(light.position - fragPos);
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

    vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 viewDir) {

      vec3 ambient = light.ambient * texture(u_albedo, uvs).xyz;
    
      vec3 norm = normalize(normal);
      vec3 lightDir = normalize(light.position - fragPos);
      float diff = max(dot(norm, lightDir), 0.0f);
      vec3 diffuse = light.diffuse * diff * texture(u_albedo, uvs).xyz;

      vec3 reflectDir = reflect(-light.direction, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
      vec3 specular = light.specular * spec * texture(u_specular, uvs).xyz;

      float distance = length(light.position - fragPos);
      float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic
        * (distance * distance));
    
      float theta = dot(lightDir, normalize(-light.direction));
      float epsilon = light.cutOff - light.outerCutOff;
      float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

      ambient  *= intensity * light.intensity;
      diffuse  *= intensity * light.intensity;
      specular *= intensity * light.intensity;

      return (ambient + diffuse + specular);
      
    }

    // --------------------------------------------------------------------- //

    void main() {
      CompoundLights();

      vec3 view_dir = normalize(camera_pos - fragPos);

      vec3 directionals = vec3(0.0, 0.0, 0.0);
      for(int i = 0; i < num_directionals; ++i){
        directionals += CalculateDirectionalLight(directional_lights[i], normal, view_dir);
      }
       
      vec3 point = vec3(0.0, 0.0, 0.0);
      for(int i = 0; i < num_points; ++i){
        point += CalculatePointLight(point_lights[i], normal, view_dir);
      }
       
      vec3 spot = vec3(0.0, 0.0, 0.0);
      for(int i = 0; i < num_spots; ++i){
        spot += CalculateSpotLight(spot_lights[i], normal, view_dir);
      }

      vec3 result = directionals + point + spot;
      
      fragColor = vec4(result, 1.0f);
    }

  )FSHADER";

  // --------------------------- DefaultShaders ---------------------------- //

  // ---------------------------- PhongShaders ----------------------------- //

  static const char* phong_vertex_shader = R"VPHONGSHADER(
    #version 330

    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uvs;
    
    uniform vec4 u_data[47];

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
    out vec3 fragPos;
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
      fragPos = (u_m_matrix * vec4(a_position, 1.0f)).xyz;
      //normal = normalize((u_m_matrix * vec4(a_normal, 0.0))).xyz;
      normal = mat3(transpose(inverse(u_m_matrix))) * a_normal;  
      uvs = a_uvs;
      time = u_time;
	    gl_Position = accum_matrix * vec4(a_position, 1.0f);
    }
  
  )VPHONGSHADER";

  static const char* phong_fragment_shader = R"FPHONGSHADER(
    #version 330
 
    struct DirectionalLight{
      vec3 direction;
    
      vec3 specular;
      vec3 diffuse;
      vec3 ambient;
      vec3 color;

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

      float intensity;      

    };

    uniform vec4 u_data[47];

    #define camera_pos vec3(u_data[13].x, u_data[13].y, u_data[13].z)
    #define num_lights u_data[14].x

    out vec4 fragColor;

    in vec4 color;
    in vec3 normal;
    in vec3 fragPos;
    in vec2 uvs;
    in float time;

    int num_directionals = 0;
    int num_points = 0;
    int num_spots = 0;

    #define max_lights 4
    
    DirectionalLight directional_lights[max_lights];
    PointLight point_lights[max_lights];
    SpotLight spot_lights[max_lights];

    // --------------------------------------------------------------------- //

    void CompoundLights(){
      int offset = 0;
      for(int i = 0; i < num_lights; ++i){
        switch(int(u_data[16 + (offset)].a)){
          case 0:
            DirectionalLight d_light;
            d_light.direction = vec3(u_data[15 + (offset)].x, u_data[15 + (offset)].y, u_data[15 + (offset)].z);
            d_light.color     = vec3(u_data[16 + (offset)].x, u_data[16 + (offset)].y, u_data[16 + (offset)].z);
            d_light.ambient   = vec3(u_data[17 + (offset)].x, u_data[17 + (offset)].y, u_data[17 + (offset)].z);
            d_light.diffuse   = vec3(u_data[18 + (offset)].x, u_data[18 + (offset)].y, u_data[18 + (offset)].z);
            d_light.specular  = vec3(u_data[19 + (offset)].x, u_data[19 + (offset)].y, u_data[19 + (offset)].z);
            d_light.intensity = u_data[17 + offset].a;
            directional_lights[num_directionals] = d_light;
            num_directionals++;
            offset += 5;
            break;
          case 1:
            PointLight p_light;
            p_light.position  = vec3(u_data[15 + (offset)].x, u_data[15 + (offset)].y, u_data[15 + (offset)].z);
            p_light.color     = vec3(u_data[16 + (offset)].x, u_data[16 + (offset)].y, u_data[16 + (offset)].z);
            p_light.ambient   = vec3(u_data[17 + (offset)].x, u_data[17 + (offset)].y, u_data[17 + (offset)].z);
            p_light.diffuse   = vec3(u_data[18 + (offset)].x, u_data[18 + (offset)].y, u_data[18 + (offset)].z);
            p_light.specular  = vec3(u_data[19 + (offset)].x, u_data[19 + (offset)].y, u_data[19 + (offset)].z);
            p_light.constant  = u_data[20 + (offset)].x;
            p_light.linear    = u_data[20 + (offset)].y;
            p_light.quadratic = u_data[20 + (offset)].z;
            p_light.intensity = u_data[17 + offset].a;
            point_lights[num_points] = p_light;
            num_points++;
            offset += 6;
            break;
          case 2:
            SpotLight s_light;
            s_light.direction = vec3(u_data[15 + (offset)].x, u_data[15 + (offset)].y, u_data[15 + (offset)].z);
            s_light.position  = vec3(u_data[16 + (offset)].x, u_data[16 + (offset)].y, u_data[16 + (offset)].z);
            s_light.color     = vec3(u_data[17 + (offset)].x, u_data[17 + (offset)].y, u_data[17 + (offset)].z);
            s_light.ambient   = vec3(u_data[18 + (offset)].x, u_data[18 + (offset)].y, u_data[18 + (offset)].z);
            s_light.diffuse   = vec3(u_data[19 + (offset)].x, u_data[19 + (offset)].y, u_data[19 + (offset)].z);
            s_light.specular  = vec3(u_data[20 + (offset)].x, u_data[20 + (offset)].y, u_data[20 + (offset)].z);
            s_light.constant  = u_data[21 + (offset)].x;
            s_light.linear    = u_data[21 + (offset)].y;
            s_light.quadratic = u_data[21 + (offset)].z;            
            s_light.cutOff    = u_data[22 + (offset)].x;            
            s_light.outerCutOff = u_data[22 + (offset)].y; 
            s_light.intensity = u_data[18 + offset].a;           
            spot_lights[num_spots] = s_light;
            num_spots++;
            offset += 8;
            break;
        }
      }
    }

    // --------------------------------------------------------------------- //

    vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir){
  
      vec3 lightDir = normalize(-light.direction);
      
      float diff = max(dot(normal, lightDir), 0.0f);
      vec3 reflectDir = reflect(-lightDir, normal);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);

      vec3 ambient  = light.ambient  * light.intensity * color.xyz;
      vec3 diffuse  = light.diffuse  * light.intensity * diff * color.xyz;
      vec3 specular = light.specular * light.intensity * spec * color.xyz;

      return (ambient + diffuse + specular);

    }

    // --------------------------------------------------------------------- //

    vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDir) {

    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    

    vec3 ambient  = light.ambient ;
    vec3 diffuse  = light.diffuse ;
    vec3 specular = light.specular;
    ambient  *= attenuation * light.intensity * color.xyz;
    diffuse  *= attenuation * light.intensity * diff * color.xyz;
    specular *= attenuation * light.intensity * spec * color.xyz;

    return (ambient + diffuse + specular);

    }

    // --------------------------------------------------------------------- //

    vec3 CalculateSpotLight(SpotLight light, vec3 normal) {

      vec3 ambient = light.ambient * color.xyz;
    
      vec3 norm = normalize(normal);
      vec3 lightDir = normalize(light.position - fragPos);
      float diff = max(dot(norm, lightDir), 0.0f);
      vec3 diffuse = light.diffuse * diff * color.xyz;

      vec3 viewDir = normalize(camera_pos - fragPos);
      vec3 reflectDir = reflect(-light.direction, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
      vec3 specular = light.specular * spec * color.xyz;

      float distance = length(light.position - fragPos);
      float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic
        * (distance * distance));
    
      float theta = dot(lightDir, normalize(-light.direction));
      float epsilon = light.cutOff - light.outerCutOff;
      float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

      ambient  *= intensity * light.intensity;
      diffuse  *= intensity * light.intensity;
      specular *= intensity * light.intensity;

      return (ambient + diffuse + specular) * light.intensity;
      
    }

    // --------------------------------------------------------------------- //

    void main() {
      CompoundLights();
      
      vec3 view_dir = normalize(camera_pos - fragPos);

      vec3 directionals = vec3(0.0, 0.0, 0.0);
      for(int i = 0; i < num_directionals; ++i){
        directionals += CalculateDirectionalLight(directional_lights[i], normal, view_dir);
      }
       
      vec3 point = vec3(0.0, 0.0, 0.0);
      for(int i = 0; i < num_points; ++i){
        point += CalculatePointLight(point_lights[i], normal, view_dir);
      }
       
      vec3 spot = vec3(0.0, 0.0, 0.0);
      for(int i = 0; i < num_spots; ++i){
        spot += CalculateSpotLight(spot_lights[i], normal);
      }

      vec3 result = directionals + point + spot;
      
      fragColor = vec4(result, 1.0f);
    }

  )FPHONGSHADER";

  // ---------------------------- PhongShaders ----------------------------- //

}

#endif // __INTERNAL_SHADERS_H__
