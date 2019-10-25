#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;

// texture samplers
uniform sampler2D diffuse;

void main()
{
    FragColor = texture(diffuse, TexCoord);
   // FragColor= vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
