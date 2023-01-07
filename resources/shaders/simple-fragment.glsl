#version 430 core

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform sampler2D Texture;
uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform Material material;

in vec2 TexturePos;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexturePos));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexturePos));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexturePos));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexturePos));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexturePos));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexturePos));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main() {
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 dirLightColor = calcDirLight(dirLight, Normal, viewDir);
    vec3 pointLightColor = CalcPointLight(pointLight, Normal, FragPos, viewDir);
    FragColor = vec4(dirLightColor, 1.0) + vec4(pointLightColor, 1.0f);
}