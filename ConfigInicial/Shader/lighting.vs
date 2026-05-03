#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
// Nuevas entradas para los huesos (coinciden con los layouts 3 y 4 de tu Mesh.h)
layout (location = 3) in ivec4 boneIds; 
layout (location = 4) in vec4 weights;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

// Máximo de huesos permitidos en tu esqueleto
const int MAX_BONES = 200;
const int MAX_BONE_INFLUENCE = 4;

// Arreglo que recibirá las transformaciones de cada hueso en el frame actual
uniform mat4 finalBonesMatrices[MAX_BONES];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 totalPosition = vec4(0.0f);
    vec3 totalNormal = vec3(0.0f);
    
    // Calculamos la posición final del vértice promediando la influencia de sus huesos
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue; // Si el ID es -1, significa que no hay hueso en este espacio
            
        if(boneIds[i] >= MAX_BONES) 
        {
            totalPosition = vec4(aPos, 1.0f);
            break;
        }
        
        // Transformamos la posición y la normal del vértice según la matriz del hueso
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(aPos, 1.0f);
        totalPosition += localPosition * weights[i];
        
        vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * aNormal;
        totalNormal += localNormal * weights[i];
    }
    
    // Fallback: si el vértice no tiene huesos (ej. el piso o la pelota), usamos su posición original
    if(totalPosition == vec4(0.0f)) {
        totalPosition = vec4(aPos, 1.0f);
        totalNormal = aNormal;
    }

    FragPos = vec3(model * totalPosition);
    Normal = mat3(transpose(inverse(model))) * totalNormal;  
    TexCoords = aTexCoords;
    
    gl_Position = projection * view * model * totalPosition;
}