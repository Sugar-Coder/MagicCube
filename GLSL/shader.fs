#version 330 core
struct Material {
    sampler2D diffuse;
    // vec3 specular;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

// uniform sampler2D texture1;  // now use Material.diffuse
uniform vec4 ourColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);  // 光线方向
    float diff = max(dot(norm, lightDir), 0.0);  // 点乘，计算光源对当前片段实际的漫发射影响

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); // 反射光线方向
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

    vec3 result = ambient + diffuse + specular;

    FragColor = ourColor * vec4(result, 1.0);
    // FragColor = ourColor * texture(texture1, TexCoord);
}
