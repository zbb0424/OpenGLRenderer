#version 430 core

layout(location = 0) out vec4 FragColor;
 
 struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 v_TexCoord;
in vec3 FragPos;
in vec3 Normal;

//uniform sampler2D texture0;
//uniform sampler2D texture1;
uniform Material material;
uniform Light light;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	//vec4 objectColor = mix(texture(texture0, v_TexCoord), texture(texture1, v_TexCoord), 0.8);

    vec3 ambient = material.ambient * light.ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light.specular;

    FragColor = vec4((ambient + diffuse + specular), 1.0);
};



