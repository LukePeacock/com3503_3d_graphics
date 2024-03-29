#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
  sampler2D diffusemap;
  sampler2D specularmap;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
     
    float constant;
    float linear;
    float quadratic;
     
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct DirLight {
   vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform vec3 viewPos;
uniform DirLight dirLight;
uniform SpotLight spotLight;
uniform bool spotlightOn;
uniform bool generalLightOn;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0f);
    if (generalLightOn)
        result = CalcDirLight(dirLight, norm, viewDir);
    if (spotlightOn)
        result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    FragColor = vec4(result, 1.0);
}
// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffusemap, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffusemap, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specularmap, TexCoords));
    return (ambient + diffuse + specular);
}


// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);    //calc light direction
    
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffusemap, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffusemap, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specularmap, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
