#version 430 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 texturePos;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat3 normalMatrix;

out vec2 TexturePos;
out vec3 Normal;
out vec3 FragPos;

void main() {
    gl_Position = projection * view * model *vec4(vertexPos, 1.0);
    TexturePos = texturePos;
    FragPos = vec3(model * vec4(vertexPos, 1.0));
    Normal = normalize(normalMatrix * normal);
}