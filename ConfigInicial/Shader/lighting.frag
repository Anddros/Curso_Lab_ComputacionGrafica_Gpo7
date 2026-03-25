#version 330 core
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

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Material material2;
uniform Light light;
uniform Light light2;

uniform sampler2D texture_diffusse;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Luz 1
    // Ambient 1
    vec3 ambient1 = light.ambient * material.diffuse;
    
    // Diffuse 1
    vec3 lightDir1 = normalize(light.position - FragPos);
    float diff1 = max(dot(norm, lightDir1), 0.0);
    vec3 diffuse1 = light.diffuse * diff1 * material.diffuse; // Corregido: diff1
    
    // Specular 1
    vec3 reflectDir1 = reflect(-lightDir1, norm);
    float spec1 = pow(max(dot(viewDir, reflectDir1), 0.0), material.shininess);
    vec3 specular1 = light.specular * (spec1 * material.specular);


    // Luz 2
    // Ambient 2
    vec3 ambient2 = light2.ambient * material2.diffuse; // Cuidado: Aquí decia light.ambient, lo cambié a light2.ambient
    
    // Diffuse 2
    vec3 lightDir2 = normalize(light2.position - FragPos);
    float diff2 = max(dot(norm, lightDir2), 0.0);
    vec3 diffuse2 = light2.diffuse * diff2 * material2.diffuse;
    
    // Specular 2
    vec3 reflectDir2 = reflect(-lightDir2, norm);
    float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0), material2.shininess);
    vec3 specular2 = light2.specular * (spec2 * material2.specular);
    

    // Sumamos la aportación de la luz 1 y la luz 2
    vec3 result = (ambient1 + diffuse1 + specular1) + (ambient2 + diffuse2 + specular2);
    
    color = vec4(result, 1.0f) * texture(texture_diffusse, TexCoords);
}