#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 offset;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = vec2(aTexCoord.x, aTexCoord.y) + offset;
    FragPos = vec3(model * vec4(aPos, 1.0));
}