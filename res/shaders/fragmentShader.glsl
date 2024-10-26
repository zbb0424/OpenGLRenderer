#version 430 core

layout(location = 0) out vec4 FragColor;
 
 struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec2 TexCoord;
in vec3 modelPos;
in vec3 Normal;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
    //ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
    
    //diffuse
    vec3 normalWorld = normalize(Normal);
    vec3 dirToLight = normalize(light.position - modelPos);
    float diff = max(dot(normalWorld, dirToLight), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

    //specular
    vec3 viewDir = normalize(viewPos - modelPos);
    vec3 reflectDir = reflect(-dirToLight, normalWorld);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
     
    //spotlight
    float theta = dot(dirToLight,normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon,0.0,1.0);
    diffuse  *= intensity;
    specular *= intensity;

    //attenuation
    float distance = length(light.position - modelPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
            light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
};



