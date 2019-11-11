    #version 330

    out vec4 fragColor;
    
    uniform vec4 u_color;
    in vec3 normal;
    in vec3 FragPos;  
    vec3 light_dir = vec3(0, 0, 1);
    vec3 light_color = vec3(1, 0, 0);
    float intensity = 0.5;

//---------------------------------------------------------------------------//

vec3 CreateDiffuseLight(vec3 lightDirection){

	vec3 norm = normalize(normal);
	float diffs = max(dot(norm, -lightDirection), 0.0f);
	vec3 diffuseLight = diffs * vec3(light_color);

	return diffuseLight;
}

//---------------------------------------------------------------------------//

    void main(){

        vec3 lightColor = vec3(0, 1, 1);
        float ambientStrength = 0.5;
        vec3 ambient = ambientStrength * lightColor;

        vec3 norm = normalize(normal);
        vec3 lightDir = normalize(vec3(0, 0, -2) - FragPos);  
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        vec3 result = (ambient + diffuse) * vec3(u_color);
        fragColor = vec4(result, 1.0);
    }