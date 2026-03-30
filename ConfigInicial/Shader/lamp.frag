#version 330 core
out vec4 FragColor;

in vec2 TexCoords; // Recibimos las coordenadas del VS

uniform sampler2D texture_diffuse1; // El nombre que la clase Model usa por defecto

void main()
{
    // Usamos la textura en lugar de vec4(1.0f)
    FragColor = texture(texture_diffuse1, TexCoords);
    
    // Opcional: Si quieres que brillen un poco más (efecto emisivo)
    // FragColor = texture(texture_diffuse1, TexCoords) * 1.5f;
}