#version 430 core

layout(location = 0) out vec4 FragColor;
 
in vec2 v_TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec4 objectColor = mix(texture(texture0, v_TexCoord), texture(texture1, v_TexCoord), 0.8);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    float specularStrength = 0.9;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    FragColor = vec4((ambient + diffuse + specular), 1.0) * objectColor;
};



