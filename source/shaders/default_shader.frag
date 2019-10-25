#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

uniform Material material;
// texture samplers
uniform sampler2D diffuse;

void main()
{
    //FragColor = texture(diffuse, TexCoord);
    FragColor = vec4(material.ambient, 1.0f);
}
