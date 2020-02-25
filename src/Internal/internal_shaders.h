// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#ifndef __INTERNAL_SHADERS_H__
#define __INTERNAL_SHADERS_H__

namespace Suffer {
  // ----------------------- RenderToTextureShaders ------------------------ //

  // TODO: Implement this fucking shit <-- John Carmack please
  static const char* harakiri_shader = R"VHARAKIRI(
  struct DirectionalLight{
      5 vec4[20]
      vec3 direction;
    
      vec3 specular;
      vec3 diffuse;
      vec3 ambient;
      vec3 color;

  };

  struct PointLight{
      6 vec4[24]
      vec3 position;
      vec3 specular;
      vec3 diffuse;
      vec3 ambient;
      vec3 color;
      float constant;
      float linear;
      float quadratic;
  };

  struct SpotLight{
      8 vec4[32]
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

  };

  vec3 CreateAmbientLight(float intensity, vec3 color) {

    vec3 ambientLight = intensity * color;
    return ambientLight;

  }

  vec3 CreateDiffuseLight(float intensity, vec3 lightPos, vec3 color, vec3 normal) {

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffs = max(dot(norm, lightPos), 0.0f);
    vec3 diffuseLight = diffs * color * intensity;

    return diffuseLight;

  }

  vec3 CreateSpecularLight(float intensity, vec3 lightPos, vec3 color, vec3 normal) {

    vec3 norm = normalize(normal);
    float specularStrength = intensity;
    vec3 reflectDirection = reflect(-lightPos, norm);
    float spec = pow(max(dot(lightPos, reflectDirection), 0.0), 32);
    vec3 specular = specularStrength * spec * color;
    vec4 texel_specular = texture2D(u_texture_specularity, uv_ * 5.0);

    return specular * vec3(texel_specular);

  }

  vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {

    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0f);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 ambient = CreateAmbientLight(1.0f, vec3(1, 1, 1));
    vec3 diffuse = CreateDiffuseLight(u_light_diffuse_intensity, lightDir, vec3(u_light_diffuse_color), normal);
    vec3 specular = CreateSpecularLight(u_light_specular_intensity, lightDir, vec3(u_light_specular_color), normal);

    return (ambient + diffuse + specular);

  }

  vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDir) {

    vec3 lightDir = normalize(light.position - FragPos);

    float diff = max(dot(normal, lightDir), 0.0f);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 ambient = CreateAmbientLight(1.0f, vec3(1, 1, 1));

    vec3 diffuse = CreateDiffuseLight(u_light_diffuse_intensity, lightDir, vec3(u_light_diffuse_color), normal);
    vec3 specular = CreateSpecularLight(u_light_specular_intensity, lightDir, vec3(u_light_specular_color), normal);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic
      * (distance * distance));

    ambient *= attenuation * pointLightIntensity;
    diffuse *= attenuation * pointLightIntensity;
    specular *= attenuation * pointLightIntensity;

    light.specular = specular;
    light.diffuse = diffuse;
    light.ambient = ambient;

    return (ambient + diffuse + specular) * u_point_color;

  }

  vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPosition, vec3 viewDir) {

    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 ambient = CreateAmbientLight(1.0f, vec3(1, 1, 1));
    vec3 diffuse = CreateDiffuseLight(u_light_diffuse_intensity, lightDir, vec3(u_light_diffuse_color), normal);
    float distance = length(light.position - fragPosition);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic
      * (distance * distance));
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = cos(radians(light.cutOff)) - cos(radians(light.outerCutOff));
    float intensity = clamp((theta - cos(radians(light.outerCutOff))) / epsilon, 0.0, 1.0);

    vec3 specular = light.specular * spec;
    ambient *= attenuation * intensity * spotLightIntensity;
    diffuse *= attenuation * intensity * spotLightIntensity;
    specular *= attenuation * intensity * spotLightIntensity;

    return (ambient + diffuse + specular);

  }

  )VHARAKIRI";


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
  
  )VUNLITSHADER";

  static const char* unlit_fragment_shader = R"FUNLITSHADER(
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

    void CompoundLights(){
      int offset = 0;
      for(int i = 0; i < num_lights; ++i){
        if(bool(u_data[15 + (offset)].a)){
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
    }

    // --------------------------------------------------------------------- //

    vec3 CreateAmbientLight(float intensity, vec3 color) {

      vec3 ambientLight = intensity * color;
      return ambientLight;

    }

    vec3 CreateDiffuseLight(float intensity, vec3 lightDir, vec3 color, vec3 normal) {

      vec3 norm = normalize(normal);

      float diffs = max(dot(norm, -lightDir), 0.0f);
      vec3 diffuseLight = diffs * color * intensity;

      return diffuseLight;

    }

    vec3 CreateSpecularLight(float intensity, vec3 lightPos, vec3 color, vec3 normal) {

      vec3 norm = normalize(normal);
      vec3 reflectDirection = reflect(-lightPos, norm);
      float spec = pow(max(dot(lightPos, reflectDirection), 0.0f), 32);
      vec3 specular = intensity * spec * color;

      return specular;

    }

    // --------------------------------------------------------------------- //

    vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir){
  
      vec3 lightDir = normalize(-light.direction);

      vec3 ambient = CreateAmbientLight(light.intensity, light.ambient);
      vec3 diffuse = CreateDiffuseLight(light.intensity, lightDir, light.diffuse, normal);
      vec3 specular = CreateSpecularLight(light.intensity, lightDir, light.specular, normal);

      return (ambient + diffuse + specular);

    }


    vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDir) {

      vec3 lightDir = normalize(light.position - fragPos);

      float diff = max(dot(normal, lightDir), 0.0f);

      vec3 reflectDir = reflect(-lightDir, normal);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

      vec3 ambient = CreateAmbientLight(1.0f, light.ambient);

      vec3 diffuse = CreateDiffuseLight(light.intensity, lightDir, vec3(light.diffuse), normal);
      vec3 specular = CreateSpecularLight(light.intensity, lightDir, vec3(light.specular), normal);

      float distance = length(light.position - fragPos);
      float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic
        * (distance * distance));

      ambient  *= attenuation *  light.intensity;
      diffuse  *= attenuation *  light.intensity;
      specular *= attenuation *  light.intensity;

      //light.specular = specular;
      //light.diffuse = diffuse;
      //light.ambient = ambient;

      return (ambient + diffuse + specular) * light.color;

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

      vec3 result = directionals + point;
      
      fragColor = vec4(result, 1.0f);
    }

  )FUNLITSHADER";

  // --------------------------- UnlitShaders ---------------------------- //

}

#endif // __INTERNAL_SHADERS_H__
